#include "bitmap.h"

#include <iostream>
#include <string>

// forces local linkage
namespace  {
int log2(int n) {
    int ans = 0;
    while(n >>= 1) ++ans;
    return ans;
}

int ceilDiv(int a, int b) {
    return (a + b - 1)/b;
}

// receives the number of elements of the bitmap
// returns an integer K meaning that we'll store information for every K consecutive entries
int rankSamplingFactor(int n) {
    return std::max(1, log2(n)); // taking the maximum makes the case n = 1 work 
}

// Section 4.3.1 of the book
int selectSamplingFactor(int n) {
    return std::max(2, log2(n) * log2(n)); // taking the maximum makes the case n = 1 work
}
}

Bitmap::Bitmap(std::shared_ptr<const std::vector<bool>> initVec) 
    : vectorRef_(initVec), n_(initVec->size()) {
    
    int b = rankSamplingFactor(n_);
    
    // precomputation of rank.
    // store results every b elements
    int rankCount = 0;
    for(size_t i = 0; i < n_; ++i) {
        rankCount += (vectorRef_->at(i) == 0);
        if (i % b == 0) {
            rank0_.push_back(rankCount);
        }
    }

    // precomputation of select.
    // store results every s elements.
    int s = selectSamplingFactor(n_);
    for(int val : {0, 1}) {
        int selectCount = 0;
        for(size_t i = 0; i < n_; ++i) {
            selectCount += vectorRef_->at(i) == val;
            if(selectCount % s == 1 && vectorRef_->at(i) == val) {
                select_[val].push_back(i);
            }
        }
        m_[val] = selectCount;
        select_[val].push_back(n_);
    }
}

// Makes a copy, as we don't have guarantees on the life time of the passed vector.
// Calling `make_shared` produces the copy and then we call the main constructor that only copies the reference
Bitmap::Bitmap(const std::vector<bool>& initVec) : Bitmap(std::make_shared<const std::vector<bool>>(initVec)) {}

Bitmap::Bitmap(const std::vector<int>& initVec) : Bitmap(std::vector<bool>(initVec.begin(), initVec.end())) {}

bool Bitmap::get(int i) const {
    return vectorRef_->at(i);
}

size_t Bitmap::size() const {
    return vectorRef_->size();
}

int Bitmap::memory() const {
    return rank0_.size() + select_[0].size() + select_[1].size();
}

int Bitmap::rank(int val, int idx) const {
    if(idx < 0 || idx >= int(n_)) {
        throw std::invalid_argument("rank index is invalid: " + std::to_string(idx));
    }
    int b = rankSamplingFactor(n_);
    int answer = rank0_[idx / b];

    for(int i = 1; i <= idx % b; ++i) {
        answer += get(b * (idx / b) + i) == 0;
    }
    return val ? idx + 1 - answer : answer;
}

int Bitmap::select(int val, int k) const {
    int s = selectSamplingFactor(n_);
    // we know that the answer lies between select_[val][ceil(k / s)-1] and select_[val][ceil(k / s)] -1
    int initRange = select_[val][ceilDiv(k,s) - 1];
    int endRange = select_[val][ceilDiv(k,s)] - 1;
    if(initRange < 0 || endRange < 0 || initRange > 1e6 || endRange > 1e6) {
        std::cout << " n = " << n_ << std::endl;
        std::cout << "m = " << m_[0] << " " << m_[1] << std::endl;
        std::cout << "val = " << val << " B[0] =" << get(0) << std::endl;
        std::cout << " k = " << k << std::endl;
        std::cout << "ceilDiv(k, s) = " << ceilDiv(k, s) << std::endl;
        std::cout << "select_[val].size() " << select_[val].size() << std::endl;
        std::cout << "weird: init, end" << initRange << " " << endRange << std::endl; 
    }


    while(initRange != endRange) {
        int mid = (initRange + endRange)/2;
        if(rank(val, mid) >= k) {
            endRange = mid;    
        } else {
            initRange = mid + 1;
        }
    }
    
    return initRange;
}
