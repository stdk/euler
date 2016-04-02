include_directories("../inc")
include_directories("..")

add_executable(util "util.cpp")
target_link_libraries(util primes)

add_executable(problems "problems.cpp")

add_executable(misc "misc.cpp")