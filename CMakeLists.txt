cmake_minimum_required(VERSION 2.6)

project(euler)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories("inc")

add_executable(problem4 "src/problem4.cpp" "src/primes.cpp")

add_executable(problem11 "src/problem11.cpp")

add_executable(problem12 "src/problem12.cpp" "src/primes.cpp")

add_executable(problem14 "src/problem14.cpp")

add_executable(problem15 "src/problem15.cpp")

add_executable(problem16 "src/problem16.cpp")
target_link_libraries(problem16 gmp gmpxx)

add_executable(problem18 "src/problem18.cpp")

add_executable(problem20 "src/problem20.cpp")
target_link_libraries(problem20 gmp gmpxx)
