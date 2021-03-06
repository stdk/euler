#include <iostream>
#include <tuple>
#include <vector>
#include <primes.h>
#include <numeric>
#include <functional>

inline size_t divisors_count(const Factors &factors) {
    return std::accumulate(factors.begin(), factors.end(), (size_t)1, [](size_t a, Factor b) {
        return a * (b.count + 1);
    });
}

int main() {
    const prime_t limit = 1000000;
    auto primes = PrimeNumbers(limit);
    const size_t divisor_limit = 500;
    
    size_t triangular = 0;
    for(size_t i=1;i<1000000;i++) {        
        triangular += i;

        auto factors = factorize(triangular, primes);
        if(divisors_count(factors) > divisor_limit) {
            std::cout << triangular << std::endl;
            break;
        }
    }
    
    return 0;
}
