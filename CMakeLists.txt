cmake_minimum_required(VERSION 2.6)

#cmake -G"Eclipse CDT4 - MinGW Makefiles" -DCMAKE_ECLIPSE_VERSION=4.4 -DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE -DCMAKE_CXX_COMPILER_ARG1=-std=gnu++14 ..

project(euler)

set (CMAKE_BUILD_TYPE Release)
set (CMAKE_CXX_COMPILER_ARG1 -std=gnu++14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_custom_target(copy_files ALL
                   COMMAND rm -rf ${CMAKE_BINARY_DIR}/input
				   COMMAND cp -R ${CMAKE_CURRENT_SOURCE_DIR}/input ${CMAKE_BINARY_DIR}
				   COMMAND rm -f ${CMAKE_BINARY_DIR}/*.py
                   COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.py ${CMAKE_BINARY_DIR}                
                 )

add_subdirectory(cppformat)
add_subdirectory(test)

include_directories("inc")

add_library(primes "src/primes.cpp")

add_executable(problem4 "src/problem4.cpp")
target_link_libraries(problem4 primes)

add_executable(problem11 "src/problem11.cpp")

add_executable(problem12 "src/problem12.cpp")
target_link_libraries(problem12 primes)

add_executable(problem14 "src/problem14.cpp")

add_executable(problem15 "src/problem15.cpp")

add_executable(problem16 "src/problem16.cpp")
target_link_libraries(problem16 gmp gmpxx)

add_executable(problem18 "src/problem18.cpp")

add_executable(problem20 "src/problem20.cpp")
target_link_libraries(problem20 gmp gmpxx)

add_executable(problem22 "src/problem22.cpp")

add_executable(problem23 "src/problem23.cpp")
target_link_libraries(problem23 primes)

add_executable(problem24 "src/problem24.cpp")

add_executable(problem25 "src/problem25.cpp")
target_link_libraries(problem25 gmp gmpxx)

add_executable(problem26 "src/problem26.cpp")
target_link_libraries(problem26 primes)

add_executable(problem27 "src/problem27.cpp")
target_link_libraries(problem27 primes)

add_executable(problem29 "src/problem29.cpp")

add_executable(problem33 "src/problem33.cpp")

add_executable(problem34 "src/problem34.cpp")

add_executable(problem35 "src/problem35.cpp")
target_link_libraries(problem35 primes)

add_executable(problem37 "src/problem37.cpp")
target_link_libraries(problem37 primes)

add_executable(problem41 "src/problem41.cpp")
target_link_libraries(problem41 primes)

add_executable(problem42 "src/problem42.cpp")

add_executable(problem45 "src/problem45.cpp")

add_executable(problem46 "src/problem46.cpp")
target_link_libraries(problem46 primes)

add_executable(problem47 "src/problem47.cpp")
target_link_libraries(problem47 primes)

add_executable(factor "src/factor.cpp")
target_link_libraries(factor primes)

add_executable(problem48 "src/problem48.cpp")

add_executable(problem49 "src/problem49.cpp")
target_link_libraries(problem49 primes)

add_executable(problem50 "src/problem50.cpp")
target_link_libraries(problem50 primes)

add_executable(problem51 "src/problem51.cpp")
target_link_libraries(problem51 primes)

add_executable(problem52 "src/problem52.cpp")

add_executable(problem53 "src/problem53.cpp")

add_executable(problem54 "src/problem54.cpp")

add_executable(problem55 "src/problem55.cpp")

add_executable(problem56 "src/problem56.cpp")
target_link_libraries(problem56 gmp gmpxx)

add_executable(problem57 "src/problem57.cpp")
target_link_libraries(problem57 gmp gmpxx)

add_executable(problem58 "src/problem58.cpp")
target_link_libraries(problem58 primes)

add_executable(problem59 "src/problem59.cpp")

add_executable(problem60 "src/problem60.cpp")
target_link_libraries(problem60 primes)

add_executable(problem61 "src/problem61.cpp")

add_executable(problem62 "src/problem62.cpp")

add_executable(problem63 "src/problem63.cpp")

add_executable(problem64 "src/problem64.cpp")

add_executable(problem65 "src/problem65.cpp")
target_link_libraries(problem65 cppformat gmp gmpxx)

add_executable(problem66 "src/problem66.cpp")
target_link_libraries(problem66 cppformat gmp gmpxx)

add_executable(problem68 "src/problem68.cpp")
target_link_libraries(problem68 cppformat)

add_executable(problem69 "src/problem69.cpp")
target_link_libraries(problem69 primes cppformat)

add_executable(problem70 "src/problem70.cpp")
target_link_libraries(problem70 primes cppformat)

add_executable(problem72 "src/problem72.cpp")
target_link_libraries(problem72 primes cppformat)

add_executable(problem73 "src/problem73.cpp")
target_link_libraries(problem73 primes cppformat)