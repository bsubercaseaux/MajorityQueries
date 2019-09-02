#include <vector>
#include <memory>

template<class T>
class Bitmap {
    public:
        Bitmap(std::shared_ptr<const std::vector<T>> initVec);

        Bitmap(const std::vector<T>& initVec);
        
        bool operator==(const Bitmap<T>& other) const {
            return (*vectorRef_) == *(other.vectorRef_);   
        }

        T get(int i) const;

        // Returns how many vals are there in the range [0, idx]
        // val is either 0 or 1.
        int rank(int val, int idx) const;

        // Returns the index of the k-th occurrence of val
        // val is either 0 or 1.
        int select(int val, int k) const;
    
    private:
        std::shared_ptr<const std::vector<T>> vectorRef_;
        std::vector<int> rank0_;
        std::vector<int> select_[2]; // allows for select_[0] and select_[1]
        int n_;


};

