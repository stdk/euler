#include <iostream>
#include <sstream>
#include <cstdint>
#include <primes.h>
#include <util.h>

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    if(argc < 2) {
        std::cerr << "Please specify a number to factorize." << std::endl;
        return 1;
    }

    std::istringstream in(argv[1]);
    uint64_t number;
    in >> number;

    Measure measure;

    const size_t limit = (size_t)sqrt(number)+1;
    const auto &primes = PrimeNumbers(limit);

    auto passed = measure.passed();
    std::cout << "Prime generation up to " << limit << " took: " << passed << " ms" << std::endl;

    auto factors = factorize(number,primes);
    for(auto factor: factors) {
        for(size_t i=0;i<factor.count;i++) {
            std::cout << factor.prime << " ";
        }
    }
    std::cout << std::endl;
    return 0;

    return 0;
}
