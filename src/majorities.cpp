#include "majorities.h"
#include "bitmap.h"

#include <algorithm>

// used for float comparisons for tau's
constexpr double EPS = 1e-7;

template<typename T, typename Bitmap>
Maj<T, Bitmap>::Maj(std::shared_ptr<const std::vector<T>> initVec, double tau) 
    : vectorRef_(initVec), tau_(tau), n_(initVec->size()) {}

// copy when a const reference is passed, to extend lifetime
template<typename T, typename Bitmap>
Maj<T, Bitmap>::Maj(const std::vector<T>& initVec, double tau) :
Maj(std::make_shared<const std::vector<T>>(initVec), tau) {}

template<typename T, typename Bitmap>
Bitmap Maj<T, Bitmap>::make_a(T x) {
    std::vector<bool> a(n_);

    for (size_t i = 0; i < n_; ++i) {
        for(size_t j = i; j < n_; ++j) {
            int count = 0;
            for(size_t k = i; k <= j; ++k) {
                count += ((*vectorRef_)[k] == x);
            }
            if(count > EPS + (j-i+1)*tau_) {
                for(size_t k = i; k <= j; ++k) {
                    a[k] = 1;
                }
            }
        }
    }

    return Bitmap(a);
}

template<typename T, typename Bitmap>
Bitmap Maj<T, Bitmap>::make_m(T x) {
    Bitmap a_x = make_a(x);
    int ones = a_x.rank(1, n_ - 1);
    std::vector<bool> m(ones, false);

    for(size_t i = 0; i < n_; ++i) {
        if(a_x.get(i) == 1) {
            m[a_x.rank(1, i) - 1] = ((*vectorRef_)[i] == x); 
        }
    }

    return Bitmap(m);
}

template<typename T, typename Bitmap>
// Uses Lemma 3, p. 8.
bool Maj<T, Bitmap>::isMajority(T x, int i, int j, double tauPrime) {
    if(tauPrime < tau_) {
        throw(std::invalid_argument("invalid tau"));
    }

    if(i < 0 || i >= n_ || j < 0 || j >= n_) {
        throw(std::invalid_argument("invalid indices"));
    }

    Bitmap a_x = make_a(x);
    int iPrime = a_x.rank(1, i);
    int jPrime = a_x.rank(1, j);

    if(jPrime - iPrime != j - i) {
        return false;
    }

    Bitmap m_x = make_m(x);

    // jPrime - 1 and iPrime - 2 instead of jPrime and iPrime-1 because of 0-indexing
    int rankJ = jPrime - 1 >= 0 ? m_x.rank(1, jPrime - 1) : 0;
    int ranjI = iPrime - 2 >= 0 ? m_x.rank(1, iPrime - 2) : 0;
    return rankJ - ranjI > tauPrime * (jPrime - iPrime + 1);
}


// Declare template implementations.
template class Maj<int, Bitmap>;
