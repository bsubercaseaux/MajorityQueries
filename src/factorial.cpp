#include "factorial.hpp"

int Factorial(int n) {
    int ans = 1;
    for(int i = 1; i <= n; ++i) {
        ans *= i;
    }
    return ans;
}
