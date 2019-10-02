#include "catch2/catch.hpp"
#include "majorities.h"
#include "bitmap.h"

TEST_CASE( "Builds A correctly", "[buildA]" ) {
    std::vector<int> test_vector = {1, 3, 2, 3, 3, 1, 1};

    Maj<int, Bitmap> maj(test_vector, 0.5);

    Bitmap a_1 = maj.make_a(1);
    Bitmap a_2 = maj.make_a(2);
    Bitmap a_3 = maj.make_a(3);

    auto target_a_1 = Bitmap({1,0,0,0,1,1,1});
    auto target_a_2 = Bitmap({0,0,1,0,0,0,0});
    auto target_a_3 = Bitmap({1,1,1,1,1,1,0});

    REQUIRE( a_1 == target_a_1 );
    REQUIRE( a_2 == target_a_2 );
    REQUIRE( a_3 == target_a_3 );
}

TEST_CASE( "Builds M correctly", "[buildM]" ) {
    std::vector<int> test_vector = {1, 3, 2, 3, 3, 1, 1};

    Maj<int, Bitmap> maj(test_vector, 0.5);

//    Bitmap m_1 = maj.make_m(1);
   // Bitmap m_2 = maj.make_m(2);
    Bitmap m_3 = maj.make_m(3);

  //  auto target_m_1 = Bitmap({1,0,1,1});
  //  auto target_m_2 = Bitmap({1});
    auto target_m_3 = Bitmap({0,1,0,1,1,0});

   // REQUIRE( m_1 == target_m_1 );
    // REQUIRE( m_2 == target_m_2 );
    REQUIRE( m_3 == target_m_3 );
}

TEST_CASE( "Lemma 3 binary majority queries", "[maj x]" ) {
    std::vector<int> test_vector = {1, 3, 2, 3, 3, 1, 1};

    Maj<int, Bitmap> maj(test_vector, 0.5);

    
    REQUIRE( maj.isMajority(1, 0, 0, 0.5)  );
    REQUIRE( not maj.isMajority(1, 0, 1, 0.5) );
    REQUIRE( not maj.isMajority(1, 0, 6, 0.5) );
    REQUIRE( maj.isMajority(1, 4, 6, 0.5) );
    REQUIRE( maj.isMajority(3, 0, 4, 0.5) );
    REQUIRE( maj.isMajority(1, 4, 6, 0.65) );
}

