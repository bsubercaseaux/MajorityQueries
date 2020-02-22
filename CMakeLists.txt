cmake_minimum_required(VERSION 4.5)
set (CMAKE_CXX_STANDARD 17)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

find_package(Catch2 REQUIRED)

project(majorityQueries LANGUAGES CXX VERSION 0.0.1)

include_directories(include)

add_subdirectory(src)
add_subdirectory(tests)

file(GLOB SOURCES "*.cpp")

