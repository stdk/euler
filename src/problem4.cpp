#include <iostream>
#include <limits>
#include <cstring>
#include <array>
#include <numeric>
#include <functional>
#include <vector>

#include <primes.h>


static bool satisfies(const std::vector<size_t> &decomposition) {
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

void check_palindromes(const std::vector<size_t> &primes) {
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
            std::cout << f << ": ";        
            for(auto value : decomposition) {
                std::cout << value << "|";
            }
            std::cout << std::endl;    
        
            if(satisfies(decomposition)) {
                break;   
            }
        }
        
        for(int j=factors.size() - 1; j>=0; j--) {
            if(!factors[j]) {
                if(j) {
                    factors[j] = max_digit;
                } else {
                    return;             
                } 
            } else {
                factors[j]--;
                break;
            }
        }
    }
}






int main() {
    auto primes = generate_primes(10000);   
    
    check_palindromes(primes);
    
    return 0;
}
