#include "bitmap.hpp"

template<class T>
Bitmap<T>::Bitmap(std::shared_ptr<const std::vector<T>> initVec) 
    : vectorRef_(initVec), n_((*initVec).size()) {
    rank0_.resize(n_+1);

    for(size_t i = 0; i < n_; ++i) {
        rank0_[i+1] = rank0_[i] + ((*vectorRef_)[i] == 0);
    }

    for(size_t i = 0; i < n_; ++i) {
        select_[(bool)((*vectorRef_)[i])].push_back(i); 
    }
}

template<class T>
Bitmap<T>::Bitmap(const std::vector<T>& initVec) : Bitmap(std::make_shared<const std::vector<T>>(initVec)) {}

template<class T>
T Bitmap<T>::get(int i) const {
    return (*vectorRef_)[i];
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

template class Bitmap<bool>;
template class Bitmap<int>;
