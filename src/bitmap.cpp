#include <vector>
#include "bitmap.h"

template<class T>
Bitmap<T>::Bitmap(std::shared_ptr<const std::vector<T>> initVec) 
    : vectorRef_(initVec), n_(initVec.size()) {
    rank0_.resize(n_+1);

    for(size_t i = 0; i < n_; ++i) {
        rank0_[i+1] = rank0_[i] + (bool)vectorRef_[i];
    }

    for(size_t i = 0; i < n_; ++i) {
        select_[(bool)vectorRef_[i]].push_back(i); 
    }
}


template<class T>
int Bitmap<T>::rank(int val, int idx) const {
    idx++; // to 1-indexing
    return val ? idx - rank0_[idx] : rank0_[idx];
}

template<class T>
int Bitmap<T>::select(int val, int k) const {
    return select_[val][k-1];
}

