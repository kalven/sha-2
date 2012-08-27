cmake_minimum_required (VERSION 2.6)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_CLANG)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -std=c++11 -Wall")
endif()

add_executable(sha256sum sha256.cpp sum256.cpp)
add_executable(sha512sum sha512.cpp sum512.cpp)
