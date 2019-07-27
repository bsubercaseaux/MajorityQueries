#include <vector>
#include "bitmap.h"

template<class T>
Bitmap<T>::Bitmap(std::shared_ptr<const std::vector<T>> initVec) 
    : vectorRef_(initVec), n_(initVec.size()) {
    rank0_.resize(n_+1);

    for(size_t i = 0; i < n_; ++i) {
        rank0_[i+1] = rank0_[i] + (bool)vectorRef_[i];
    }

    select0_.resize(rank0_[n_]);
    select1_.resize(n_ - select0_.size());

    int pos0 = 0;
    int pos1 = 0;
    for(size_t i = 0; i < n_; ++i) {
        if((bool)*vectorRef_[i]) {
            select1_[pos1++] = i;
        } else {
            select0_[pos0++] = i;
        }
    }
}


template<class T>
int Bitmap<T>::rank(int val, int idx) const {
    idx++; // to 1-indexing
    return val ? idx - rank0_[idx] : rank0_[idx];
}

template<class T>
int Bitmap<T>::select(int val, int k) const {
    return val ? select1_[k-1] : select0_[k-1];
}

