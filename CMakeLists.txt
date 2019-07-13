cmake_minimum_required(VERSION 3.5)

find_package(Catch2 REQUIRED)

project(majorityQueries LANGUAGES CXX VERSION 0.0.1)

include_directories(include)

add_subdirectory(src)
add_subdirectory(tests)

file(GLOB SOURCES "*.cpp")

