#include <iostream>
#include <primes.h>

size_t path_count(size_t square_side_length) {
    size_t sum = 1;
    size_t current = 1;
    
    std::cout << current << " ";
    for(size_t i=0;i<square_side_length;i++) {
        current = current * (square_side_length - i) / (i + 1);
        std::cout << current << " ";
        sum += current*current;
    }
    
    std::cout << std::endl;
    
    return sum;
}


int main() {
    std::cout << "Path count: " << path_count(20) << std::endl;
    
    return 0;
}
