#include <iostream>
#include <primes.h>
#include <util.h>

size_t reciprocal_cycle_length(size_t prime) {
    size_t base = 9;
    size_t result = 1;
    while(base) {
        base = (base*10 + 9) % prime;
        ++result;
    }

    return result;
}

int main() {
    const auto &primes = PrimeNumbers(1000);

    size_t longest_rcp_cycle_number = 0;
    size_t longest_rcp_cycle_length = 0;

    auto t = measure([&] {
            //no need to check 2,3,5 since 2 and 5 are exceptions to our rule for determining reciprocal cycle length
            for(auto p=primes.rbegin();p!=primes.rend()-3;++p) {
                auto length = reciprocal_cycle_length(*p);
                if(length > longest_rcp_cycle_length) {
                    longest_rcp_cycle_length = length;
                    longest_rcp_cycle_number = *p;
                }
            }
    });

    if(!util::test_mode()) {
        std::cout << "Time elapsed: " << t.count() << std::endl;
        std::cout << "Longest rcp cycle length: " << longest_rcp_cycle_length << std::endl;
        std::cout << "Longest rcp cycle number: ";
    }

    std::cout << longest_rcp_cycle_number << std::endl;

    return 0;
}
