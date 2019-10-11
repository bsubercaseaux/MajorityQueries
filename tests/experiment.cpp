#include <iostream>

#include <majorities.h>
#include <bitmap.h>
#include <fenwicktree.h>

int main() {
    std::vector<int> a = {1,3,2,3,3,1,1};
    Maj<int, Bitmap> maj {a, 0.5};
    int i = maj.findFirstMajority(1, 4, 0.5);
    std::cout << "i first maj = " << i << " and its value is " << a[i] << std::endl;
    return 0;
}
