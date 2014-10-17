#include <iostream>
#include <tuple>
#include <vector>
#include <primes.h>
#include <numeric>
#include <functional>


inline size_t divisors_count(const CompactFactors &factors) {
    return std::accumulate(factors.begin(), factors.end(), (size_t)1, [](size_t a, CompactFactor b) {
        return a * (std::get<1>(b) + 1);
    });
}

int main() {
    auto primes = generate_primes_vector(100000);
    CompactFactors factors;
    factors.reserve(10); //no more capacity should be required, since 9 unique primes give at least 512 divisors instantly
    
    const size_t divisor_limit = 500;
    
    size_t triangular = 0;
    for(size_t i=1;i<1000000;i++) {        
        triangular += i;

        if(factorize_compact(triangular, primes, factors)) {
            if(divisors_count(factors) > divisor_limit) {
                std::cout << triangular << std::endl;
                break;
            }
        } else {
            std::cout << "Need more primes to factorize: " << triangular << std::endl;
            break;
        }
    }
    
    return 0;
}
