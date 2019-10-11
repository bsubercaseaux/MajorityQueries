#include "majorities.h"
#include "bitmap.h"
#include "wavelettree.h"
#include "fenwicktree.h"

#define DEBUG std::cout << __LINE__ << std::endl

#include <set>
#include <map>
#include <algorithm>
#include <iostream>

// used for float comparisons for tau's
constexpr double EPS = 1e-7;

int findFirstBitmapFit(int i, int j, const std::vector<std::vector<int>> aVec) {
    for(int k = 0; k < aVec.size(); ++k) {
        bool fits = true;
        
        for(int l = i; l <= j; ++l) {
            if(aVec[k][l]) {
                fits = false;
                break;
            }
        }

        if(fits) {
            return k;
        }
    }
    return aVec.size();
}

template<typename T, typename Bitmap>
Maj<T, Bitmap>::Maj(std::shared_ptr<const std::vector<T>> initVec, double tau) 
    : vectorRef_(initVec), tau_(tau), n_(initVec->size()) {

    // Building C_x's in O(n^2 lg^2(n)) (conjectured)
    //
    std::set<T> elements(vectorRef_->begin(), vectorRef_->end());

    std::map<int, std::vector<std::pair<int, int>>> C; // will contain pairs representing ranges
    WaveletTree wt(vectorRef_);
    for(const T& element: elements) {
        // iterate ranges in decreasing length order, so we don't consider that many ranges contained in others. 
        // Also, if a position is already in C_element (virtual; C doesn't know to whom each range belong) we don't really neeed
        // to consider intervals starting there either.
        //
        DoubleFT ft(n_);
        for(int i = 0; i < n_; ++i) {
            for(int len = n_ - i; len >= 1;--len) {
                if(ft.query(i, i+len-1)>= len) break;
                if(wt.rank(element, i, i + len) > EPS + len*tau_) {
                    C[element].emplace_back(i, i + len - 1);
                    ft.update(i, i+len-1, 1);
                    break;
                }
            }
        }
    }

    std::vector<std::tuple<int, int, int>> Cmax;
    std::vector<std::vector<int>> aVec;
    std::vector<std::vector<bool>> mVec;
    // Building A's and M's
    for(const auto& [element, vectorIntervals]: C) {
        FenwickTree ft(n_);
        for(const auto& [i, j]: vectorIntervals) {
            ft.update(i+1, j+2, 1);
        }
        for(int i = 0; i < n_;) {
            int j = i;
            while(j < n_ && ft.query(j + 1)) {
                j++;
            }
            if(j != i) {
                Cmax.emplace_back(i, j-1, element);
            } else {
                j++;
            }
            i = j;
        }
    } 
    std::sort(Cmax.begin(), Cmax.end());
    for(const auto& [i, j, x] : Cmax) {
        int index = findFirstBitmapFit(i, j, aVec);
        if(index == aVec.size()) {
            aVec.emplace_back(n_, 0);
        }
        for(int k = i; k <= j; ++k) {
            aVec[index][k] = x;
        }
    }

    mVec.resize(aVec.size());
    for(size_t k = 0; k < aVec.size(); ++k) {
        const auto& a = aVec[k];
        for(size_t i = 0; i < a.size(); ++i) {
            if(a[i]) {
              mVec[k].push_back(vectorRef_->at(i) == a[i]);  
            }
        }   
    }

    for(const auto& a: aVec) {
        A_.emplace_back(a);
    }

    for(const auto& m: mVec) {
        M_.emplace_back(m);
    }
    
}

// copy when a const reference is passed, to extend lifetime
template<typename T, typename Bitmap>
Maj<T, Bitmap>::Maj(const std::vector<T>& initVec, double tau) :
Maj(std::make_shared<const std::vector<T>>(initVec), tau) {}


template<typename T, typename Bitmap>
int Maj<T, Bitmap>::findFirstMajority(int i, int j, double tauPrime) {
    if(tauPrime < tau_) {
        throw(std::invalid_argument("invalid tau"));
    }

    if(i < 0 || i >= n_ || j < 0 || j >= n_) {
        throw(std::invalid_argument("invalid indices"));
    }
    
    for(size_t k = 0; k < A_.size(); ++k) {
        const auto& a = A_[k];
        int iPrime = a.rank(1, i);
        int jPrime = a.rank(1, j);
        if(jPrime - iPrime != j - i) {
            continue;
        }

        const auto& m = M_[k];
        // jPrime - 1 and iPrime - 2 instead of jPrime and iPrime-1 because of 0-indexing
        int rankJ = jPrime - 1 >= 0 ? m.rank(1, jPrime - 1) : 0;
        int rankI = iPrime - 2 >= 0 ? m.rank(1, iPrime - 2) : 0;
        if(rankJ - rankI > tauPrime * (jPrime - iPrime + 1)){
            return i - iPrime + 1 + m.select(1, rankI + 1);
        }
    }
    return -1; // flag for no majority
}


// Declare template implementations.
template class Maj<int, Bitmap>;
