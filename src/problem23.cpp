#include <iostream>
#include <numeric>
#include <tuple>
#include <vector>
#include <primes.h>

const size_t abundant_representable_limit = 28123;

size_t sum_all_divisors(const CompactFactors &factors) {
    size_t sum = 1;

    for(const auto &f: factors) {
        size_t c = 0;
        for(size_t i=0,s=1;i<=std::get<1>(f);++i,s*=std::get<0>(f)) c += s;
        sum *= c;
    }

    return sum >> 1;
}

std::vector<size_t> get_abundant_numbers(size_t limit, const Primes &primes) {
    std::vector<size_t> abundant;

    for(size_t i=1;i<limit;i++) {
        auto factors = factorize_compact(i,primes);
        auto divisors_sum = sum_all_divisors(factors);
        if(i < divisors_sum) abundant.push_back(i);
    }

    return abundant;
}

int main() {
    const auto primes = generate_primes_vector(abundant_representable_limit*2);
    const auto abundant = get_abundant_numbers(abundant_representable_limit, primes);

    size_t total = abundant_representable_limit*(abundant_representable_limit-1)/2;

    std::vector<bool> abundant_representable(abundant_representable_limit, false);
    for(auto a=abundant.begin();a!=abundant.end();++a) {
        for(auto b = a;b!=abundant.end();++b) {
            size_t s = *a + *b;
            if(s < abundant_representable.size() && !abundant_representable[s]) {
                total -= s;
                abundant_representable[s] = true;
            }
        }
    }

    std::cout << "Sum of natural numbers not representable by the sum of two abundant numbers: " << total << std::endl;
    return 0;
}
