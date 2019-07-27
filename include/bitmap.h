#include <vector>

template<class T>
class Bitmap {
    private:
        std::vector<int> rank0_;
        std::vector<int> select_[2];
        std::shared_ptr<const std::vector<T>> vectorRef_;
        int n_;

    public:
        Bitmap(std::shared_ptr<const std::vector<T>> initVec);

        // Returns how many vals are there in the range [0, idx]
        // val is either 0 or 1.
        int rank(int val, int idx) const;

        // Returns the index of the k-th occurrence of val
        // val is either 0 or 1.
        int select(int val, int k) const;
};
