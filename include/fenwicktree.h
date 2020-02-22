#include <vector>

struct FenwickTree {
    std::vector<int> ft;
    
    FenwickTree(int n) {
   	    ft.resize(n+1,0);
    }

    int query(int i) {
   	 int ans = 0;
   	 for(;i;i-=i&(-i)) ans += ft[i];
   	 return ans;
    }

    int query(int i, int j) {
        return query(j) - query(i-1);
    }

    void update(int i, int v) {
   	 for(;i<int(ft.size());i+=i&(-i)) 
         ft[i] += v;
    }
    
    //Queries puntuales, Updates por rango
    // [i,j)
    void update(int i, int j, int v) {
        update(i,v); update(j,-v);
    }
};

struct DoubleFT {
    FenwickTree f1;
    FenwickTree f2;

    DoubleFT(int n) : f1(n), f2(n) {}

    int query(int i) {
        return f1.query(i+1) * i - f2.query(i+1);
    }

    int query(int i, int j) {
        return query(j) - i ? query(i-1) : 0;
    }

    void update(int i, int j, int v) {
        f1.update(i+1, v);
        f1.update(j+2, -v);
        f2.update(i+1, v * (i-1));
        f2.update(j+2, -v * j);
    }
};
