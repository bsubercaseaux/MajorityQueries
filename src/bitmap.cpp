#include "bitmap.hpp"

Bitmap::Bitmap(std::shared_ptr<const std::vector<bool>> initVec) 
    : vectorRef_(initVec), n_((*initVec).size()) {
    rank0_.resize(n_+1);

    for(size_t i = 0; i < n_; ++i) {
        rank0_[i+1] = rank0_[i] + ((*vectorRef_)[i] == 0);
    }

    for(size_t i = 0; i < n_; ++i) {
        select_[(bool)((*vectorRef_)[i])].push_back(i); 
    }
}

// Makes a copy, as we don't have guarantees on the life time of the passed vector.
// Calling `make_shared` produces the copy and then we call the main constructor that only copies the reference
Bitmap::Bitmap(const std::vector<bool>& initVec) : Bitmap(std::make_shared<const std::vector<bool>>(initVec)) {}

bool Bitmap::get(int i) const {
    return (*vectorRef_)[i];
}


int Bitmap::rank(int val, int idx) const {
    idx++; // to 1-indexing
    return val ? idx - rank0_[idx] : rank0_[idx];
}

int Bitmap::select(int val, int k) const {
    if(k > select_[val].size()) {
        throw std::invalid_argument("You asked for the k-th occurence of a value, but there are fewer");
    }
    return select_[val][k-1];
}
