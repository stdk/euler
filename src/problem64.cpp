#include <iostream>
#include <cstdint>
#include <util.h>
#include <continued_fractions.h>

/*
 * Odd period square roots
 */

int64_t period_length(uint32_t n) {
    auto perfect = perfect_square_root(n);
    if(perfect != -1) {
        return 0;
    }

    sqrt_terms_iterator initial(n);
    sqrt_terms_iterator current = ++initial;

    for(size_t i=0;;i++) {
        if(++current == initial) {
            return i+1;
        }
    }

    return -1;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    Measure measure;

    size_t count = 0;

    for(uint32_t i=1;i<=10000;i++) {
        auto len = period_length(i);
        if(len % 2 == 1) {
            count++;
        }
    }

    auto passed = measure.passed();
    if(!util::test_mode()) {
        std::cout << "Processing took " << passed << " ms" << std::endl;
        std::cout << "Count: " << count << std::endl;
    } else {
        std::cout << count << std::endl;
    }

    return 0;
}
