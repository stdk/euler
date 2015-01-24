cmake_minimum_required(VERSION 2.6)

#cmake -G"Eclipse CDT4 - MinGW Makefiles" -DCMAKE_ECLIPSE_VERSION=4.4 -DCMAKE_CXX_COMPILER_ARG1=-std=c++11 .

project(euler)

set (CMAKE_BUILD_TYPE Release)

set (CMAKE_CXX_COMPILER_ARG1 -std=c++11)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

include_directories("inc")

add_executable(test_suite "test/main.cpp")

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

add_executable(problem22 "src/problem22.cpp")

add_executable(problem23 "src/problem23.cpp" "src/primes.cpp")

add_executable(problem24 "src/problem24.cpp")

add_executable(problem25 "src/problem25.cpp")
target_link_libraries(problem25 gmp gmpxx)

add_executable(problem26 "src/problem26.cpp" "src/primes.cpp")

add_executable(problem27 "src/problem27.cpp" "src/primes.cpp")

add_executable(problem29 "src/problem29.cpp")

add_executable(problem35 "src/problem35.cpp" "src/primes.cpp")

add_executable(problem37 "src/problem37.cpp" "src/primes.cpp")

add_executable(problem41 "src/problem41.cpp" "src/primes.cpp")

add_executable(problem42 "src/problem42.cpp")

add_executable(problem45 "src/problem45.cpp")

add_executable(problem46 "src/problem46.cpp" "src/primes.cpp")

add_executable(problem47 "src/problem47.cpp" "src/primes.cpp")

add_executable(factor "src/factor.cpp" "src/primes.cpp")

add_executable(problem48 "src/problem48.cpp")

add_executable(problem49 "src/problem49.cpp" "src/primes.cpp")

add_executable(problem50 "src/problem50.cpp" "src/primes.cpp")

add_executable(problem51 "src/problem51.cpp" "src/primes.cpp")

add_executable(problem52 "src/problem52.cpp")

add_executable(problem53 "src/problem53.cpp")

add_executable(problem54 "src/problem54.cpp")

add_executable(problem55 "src/problem55.cpp")

add_executable(problem56 "src/problem56.cpp")
target_link_libraries(problem56 gmp gmpxx)

add_executable(problem57 "src/problem57.cpp")
target_link_libraries(problem57 gmp gmpxx)

add_executable(problem58 "src/problem58.cpp" "src/primes.cpp")

add_executable(problem59 "src/problem59.cpp")

add_executable(problem60 "src/problem60.cpp" "src/primes.cpp")

add_executable(problem61 "src/problem61.cpp")