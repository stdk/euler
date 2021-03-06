#include <iostream>
#include <limits>
#include <cstring>
#include <array>
#include <numeric>
#include <functional>
#include <vector>
#include <primes.h>
#include <util.h>

std::vector<size_t> expand(const Factors &factors) {
    std::vector<size_t> expansion;

    for(const auto &factor: factors) {
        for(size_t i=0;i<factor.count;++i) {
            expansion.push_back(factor.prime);
        }
    }

    return expansion;
}

template<class FactorizationExpansion>
static bool satisfies(const FactorizationExpansion &decomposition) {
    size_t a = *decomposition.rbegin();
    size_t b = 1;
    const size_t limit = 1000;
    
    for(auto i=decomposition.rbegin()+1;i!=decomposition.rend();i++) {
        if(*i * a < limit) {
            a *= *i;
        } else if(*i * b < limit) {
            b *= *i;
        } else {
            return false;   
        }
    }
    
    return a > 100 && a < limit && b > 100 && b < limit;    
}

template<class Primes>
size_t palindrome_lookup(const Primes &primes) {
    for(size_t digits=999;digits;--digits) {
        auto f = digits*1000 + reverse_digits(digits);
        auto decomposition = factorize(f, primes);
        if(decomposition.size()) {
            if(!util::test_mode()) {
                std::cout << f << ": ";
                std::cout << decomposition << std::endl;
            }
        
            if(satisfies(expand(decomposition))) {
                return f;
            }
        }
    }

    return 0;
}

int main() {
    const auto &primes = PrimeNumbers(10000);
    
    std::cout << palindrome_lookup(primes) << std::endl;
    
    return 0;
}
