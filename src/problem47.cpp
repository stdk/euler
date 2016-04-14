#include <iostream>
#include <primes.h>
#include <util.h>
#include <cstdint>

template<class P>
inline bool has_four_prime_factors(uint32_t number,const P &primes) {
    return factorize(number,primes,true).size() == 4;
}

template<class P>
size_t search(const P &primes,uint32_t limit) {
    uint32_t i = primes[0]*primes[1]*primes[2]*primes[3];
    uint8_t state = has_four_prime_factors(i,primes) |
                    has_four_prime_factors(i+1,primes)*2 |
                    has_four_prime_factors(i+2,primes)*4 |
                    has_four_prime_factors(i+3,primes)*8;

    uint32_t shift_table[] = {
            4,         //0000 0
            4,         //0001 1
            4,         //0010 2
            4,         //0011 3
            4,         //0100 4
            4,         //0101 5
            4,         //0110 6
            4,         //0111 7
            3,         //1000 8
            3,         //1001 9
            3,         //1010 A
            3,         //1011 B
            2,         //1100 C
            2,         //1101 D
            1,         //1110 E
            0,         //1111 F
    };

    while(i < limit) {
        if(state == 0xF) return i;

        uint32_t shift = shift_table[state];

        while(shift--) {
            state >>= 1;
            state += 8*has_four_prime_factors(++i + 3,primes);
        }
    }
    return 0;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    const uint32_t limit = 1000000;

    Measure measure;

    const auto &primes = PrimeNumbers(limit);

    auto passed = measure.passed();
    if(!util::test_mode()) {
        std::cout << "Prime generation took: " << passed << " ms" << std::endl;
    }

    measure.reset();
    size_t number = search(primes,limit);
    passed = measure.passed();

    if(!util::test_mode()) {
        std::cout << "Search for " << number << " took: " << passed << " ms" << std::endl;
    } else {
        std::cout << number << std::endl;
    }

    return 0;
}
