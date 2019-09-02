add_executable(test test_main.cpp test_bitmap.cpp test_maj.cpp)

target_link_libraries(test bitmap maj Catch2::Catch2)
