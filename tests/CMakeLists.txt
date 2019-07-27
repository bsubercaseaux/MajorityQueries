add_executable(test test_main.cpp test_bitmap.cpp)

target_link_libraries(test bitmap Catch2::Catch2)
