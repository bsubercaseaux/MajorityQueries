#include <vector>
#include <memory>

template<class T, class Bitmap>
class Maj {
    public:
        Maj(std::shared_ptr<const std::vector<T>> initVec, double tau);
        
        // forced to copy, as we don't have guarantees on the lifetime of the object
        Maj(const std::vector<T>& initVec, double tau);

        bool isMajority(T x, int i, int j, double tauPrime);

        Bitmap make_a(T x);
        Bitmap make_m(T x);

    private:
        std::shared_ptr<const std::vector<T>> vectorRef_;
        double tau_;
        size_t n_;
};
