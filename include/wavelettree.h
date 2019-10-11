#include <vector>
#include <memory>

typedef std::vector<int>::iterator iter;

class WaveletTree {
    std::vector<std::vector<int>> r0; int n, s;
    std::vector<int> arrCopy;

    void build(iter b, iter e, int l, int r, int u) {
        if (l == r)
            return;
        int m = (l+r)/2;
        r0[u].reserve(e-b+1); r0[u].push_back(0);
        for (iter it = b; it != e; ++it)
            r0[u].push_back(r0[u].back() + (*it<=m));
        iter p = stable_partition(b, e, [=](int i){
                                  return i<=m;});
        build(b, p, l, m, u*2);
        build(p, e, m+1, r, u*2+1);
    }

public:
    //arr[i] in [0,sigma)
    WaveletTree(std::vector<int> arr, int sigma) {
        n = arr.size(); s = sigma;
        r0.resize(s*2); arrCopy = arr;
        build(arr.begin(), arr.end(), 0, s-1, 1);
    }

    WaveletTree(std::shared_ptr<const std::vector<int>> arrRef) : WaveletTree(*arrRef, arrRef->size()) {}

    //count occurrences of x in positions [0,k)
    int rank(int x, int k) {
        int l = 0, r = s-1, u = 1, m, z;
        while (l != r) {
            m = (l+r)/2;
            z = r0[u][k]; u*=2;
            if (x <= m)
                k = z, r = m;
            else
                k -= z, l = m+1, ++u;
        }
        return k;
    }

    int rank(int x, int i, int j) {
        return rank(x, j) - rank(x, i);
    }
};

