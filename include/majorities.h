
#pragma once

#include <vector>
#include <memory>

template<class T, class Bitmap>
class Maj {
    public:
        Maj(std::shared_ptr<const std::vector<T>> initVec, double tau);
        
        // forced to copy, as we don't have guarantees on the lifetime of the object
        Maj(const std::vector<T>& initVec, double tau);
        int findFirstMajority(int i, int j, double tauPrime) const; 

        int memory() const;

    private:
        std::shared_ptr<const std::vector<T>> vectorRef_;
        
        std::vector<Bitmap> A_;
        std::vector<Bitmap> M_;
        double tau_;
        size_t n_;
        int countMem_;
};
