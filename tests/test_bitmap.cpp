#include "catch2/catch.hpp"
#include "bitmap.h"

#include <chrono>

using Clock = std::chrono::high_resolution_clock;

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

TEST_CASE( "Stress test for rank", "[stress rank]" ) {
    int n = 5 * 1e6;
    std::vector<bool> test_vector(n);

    //randomly generate test vector
    //
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,1);
    for (int i = 0; i < n; i++) {
        test_vector[i] = distribution(generator);        
    }


    auto t1 = Clock::now();
    // TIMED OPERATIONS
    Bitmap bitmap(test_vector);

    int dummyRes = 0; // just here to avoid compiler optimizing the result of bitmap.rank
    for(int i = 0; i < n; i++) {
        dummyRes += bitmap.rank(0, i); // += so it executes every step of the for loop
    }
    assert(dummyRes != 0); // consider yourself very lucky if this breaks...
    // END OF TIME OPERATIONS
    auto t2 = Clock::now();

    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    REQUIRE( millis < 3000 );
}

TEST_CASE( "Stress test for select", "[stress select]" ) {
    int n = 5 * 1e5;
    std::vector<bool> test_vector(n);

    //randomly generate test vector
    //
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,1);
    for (int i = 0; i < n; i++) {
        test_vector[i] = distribution(generator);        
    }


    auto t1 = Clock::now();
    // TIMED OPERATIONS
    Bitmap bitmap(test_vector);

    int dummyRes = 0; // just here to avoid compiler optimizing the result of bitmap.rank
    for(int i = 1; i <= n; i++) { // Attention: select is indexed [1,n]
        dummyRes += bitmap.select(0, i / 5 + 1); // += so it executes every step of the for loop
    }
    assert(dummyRes != 0); // consider yourself very lucky if this breaks...
    // END OF TIME OPERATIONS
    auto t2 = Clock::now();

    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    REQUIRE( millis < 3000 );
}

