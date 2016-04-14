#include <iostream>
#include <primes.h>
#include <cstdint>
#include <util.h>

uint64_t path_count(size_t square_side_length) {
    uint64_t sum = 1;
    uint64_t current = 1;
    
    if(!util::test_mode()) std::cout << current << " ";
    for(size_t i=0;i<square_side_length;i++) {
        current = current * (square_side_length - i) / (i + 1);
        if(!util::test_mode()) {
            std::cout << current << " ";
        }
        sum += current*current;
    }
    
    if(!util::test_mode()) std::cout << std::endl;
    
    return sum;
}


int main() {
    auto count = path_count(20);

    if(!util::test_mode()) {
        std::cout << "Path count: " << count << std::endl;
    } else {
        std::cout << count << std::endl;
    }
    
    return 0;
}
