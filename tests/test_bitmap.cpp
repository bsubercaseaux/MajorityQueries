#include "catch2/catch.hpp"
#include "bitmap.hpp"

TEST_CASE( "Rank 0 gives correct results", "[rank0]" ) {
    std::vector<bool> test_vector = {1, 0, 0, 1, 1};
    Bitmap bitmap(test_vector);
    
    REQUIRE( bitmap.rank(0, 0) == 0 );
    REQUIRE( bitmap.rank(0, 1) == 1 );
    REQUIRE( bitmap.rank(0, 2) == 2 );
    REQUIRE( bitmap.rank(0, 3) == 2 );
    REQUIRE( bitmap.rank(0, 4) == 2 );
}

TEST_CASE( "Rank 1 gives correct results", "[rank1]" ) {
    std::vector<bool> test_vector = {1, 0, 0, 1, 1};
    Bitmap bitmap(test_vector);
    
    REQUIRE( bitmap.rank(1, 0) == 1 );
    REQUIRE( bitmap.rank(1, 1) == 1 );
    REQUIRE( bitmap.rank(1, 2) == 1 );
    REQUIRE( bitmap.rank(1, 3) == 2 );
    REQUIRE( bitmap.rank(1, 4) == 3 );
}

TEST_CASE( "Select 0 gives correct results", "[select0]" ) {
    std::vector<bool> test_vector = {1, 0, 0, 1, 1};
    Bitmap bitmap(test_vector);
    
    REQUIRE( bitmap.select(0, 1) == 1 );
    REQUIRE( bitmap.select(0, 2) == 2 );
}

TEST_CASE( "Select 1 gives correct results", "[select1]" ) {
    std::vector<bool> test_vector = {1, 0, 0, 1, 1};
    Bitmap bitmap(test_vector);
    
    REQUIRE( bitmap.select(1, 1) == 0 );
    REQUIRE( bitmap.select(1, 2) == 3 );
    REQUIRE( bitmap.select(1, 3) == 4 );
}

