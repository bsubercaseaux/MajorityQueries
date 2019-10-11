add_executable(test test_main.cpp test_bitmap.cpp test_maj.cpp)
add_executable(experiment experiment.cpp)

target_link_libraries(test bitmap maj Catch2::Catch2)
target_link_libraries(experiment bitmap maj)
