#include <iostream>
#include <cmath>
#include <util.h>

/*
 * The 5-digit number, 16807=7^5, is also a fifth power.
 * Similarly, the 9-digit number, 134217728=8^9, is a ninth power.
 * How many n-digit positive integers exist which are also an nth power?
 *
 */

size_t powerful_digits_count() {
    size_t count = 0;

    for(size_t x=0;x<10;x++) {
        size_t k_max = std::floor(1 / (1 - std::log(x)/std::log(10)));
        count += k_max;
    }

    return count;
}

int main() {
    Measure measure;

    auto count = powerful_digits_count();

    auto passed = measure.passed();

    if(!util::test_mode()) {
        std::cout << "Counting took: " << passed << " ms" << std::endl;
        std::cout << "Powerful digits count: ";
    }
    std::cout << count << std::endl;

    return 0;
}
