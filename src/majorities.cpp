#include "majorities.hpp"

// used for float comparisons for tau's
constexpr double EPS = 1e-7;

template<class T>
Maj<T>::Maj(std::shared_ptr<const std::vector<T>> initVec, double tau) 
    : vectorRef_(initVec), tau_(tau), n_(initVec->size()) {}

// copy when a const reference is passed, to extend lifetime
template<class T>
Maj<T>::Maj(const std::vector<T>& initVec, double tau) :
Maj(std::make_shared<const std::vector<T>>(initVec), tau) {}

template<class T>
Bitmap Maj<T>::make_a(T x) {
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

template<class T>
Bitmap Maj<T>::make_m(T x) {
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

template<class T>
// Uses Lemma 3, p. 8.
bool Maj<T>::isMajority(T x, int i, int j, double tauPrime) {
    assert(tauPrime >= tau_);

    Bitmap a_x = make_a(x);
    int iPrime = a_x.rank(1, i);
    int jPrime = a_x.rank(1, j);

    if(jPrime - iPrime != j - i) {
        return false;
    }

    Bitmap m_x = make_m(x);

    // jPrime - 1 and iPrime - 2 instead of jPrime and iPrime-1 because of 0-indexing
    return m_x.rank(1, jPrime - 1) - m_x.rank(1, iPrime - 2) > tauPrime * (jPrime - iPrime + 1);
}


// Declare template implementations.
template class Maj<int>;
