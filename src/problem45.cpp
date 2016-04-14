#include <iostream>
#include <limits>
#include <util.h>
#include <cstdint>

uint64_t hexagonal_number(size_t n) {
    return n*(2*n-1);
}

bool is_triangle_number(uint64_t x) {
    int64_t d = perfect_square_root(8*x+1);
    if(-1 == d) return false;

    return (d-1)%2 == 0;
}

bool is_pentagonal_number(uint64_t x) {
    int64_t d = perfect_square_root(24*x+1);
    if(-1 == d) return false;

    return (d+1)%6 == 0;
}

size_t search(size_t start) {
    for(size_t n=start;n<std::numeric_limits<size_t>::max();n++) {
        uint64_t h = hexagonal_number(n);
        if(is_triangle_number(h) && is_pentagonal_number(h)) {
            return h;
        }
    }
    return 0;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    Measure measure;
    auto number = search(143+1);
    auto passed = measure.passed();

    if(!util::test_mode()) {
        std::cout << "Search for " << number << " took: " << passed << " ms" << std::endl;
    } else {
        std::cout << number << std::endl;
    }

    return 0;
}
