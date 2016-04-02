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
    const size_t max_digit = 9;
    std::array<size_t, 3> factors;
    factors.fill(max_digit);
    
    auto formula = [&]() {
        return factors[0] * 100001 + factors[1] * 10010 + factors[2] * 1100;
    };
    
    while(true) {
        auto f = formula();
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
        
        for(int j=factors.size() - 1; j>=0; j--) {
            if(!factors[j]) {
                if(j) {
                    factors[j] = max_digit;
                } else {
                    return 0;
                } 
            } else {
                factors[j]--;
                break;
            }
        }
    }
}

int main() {
    const auto &primes = PrimeNumbers(10000);
    
    std::cout << palindrome_lookup(primes) << std::endl;
    
    return 0;
}
