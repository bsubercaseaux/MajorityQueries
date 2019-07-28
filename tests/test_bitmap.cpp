#include <vector>
#include "catch.hpp"
#include "bitmap.h"

TEST_CASE( "Rank 0 gives correct results", "[rank0]" ) {
    std::vector<bool> test_vector = {1, 0, 0, 1, 1};
    std::shared_ptr<const std::vector<bool>> vector_ptr = std::make_shared<const std::vector<bool>>(test_vector);
    Bitmap<bool> bitmap(vector_ptr);
    
    REQUIRE( bitmap.rank(0, 0) == 0 );
    REQUIRE( bitmap.rank(0, 1) == 1 );
    REQUIRE( bitmap.rank(0, 2) == 2 );
    REQUIRE( bitmap.rank(0, 3) == 2 );
    REQUIRE( bitmap.rank(0, 4) == 2 );
}
