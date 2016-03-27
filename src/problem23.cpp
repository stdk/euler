#include <iostream>
#include <numeric>
#include <tuple>
#include <vector>
#include <primes.h>
#include <util.h>

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

std::vector<size_t> get_abundant_numbers(size_t limit, const PrimeNumbers &primes) {
    std::vector<size_t> abundant;

    for(size_t i=1;i<limit;i++) {
        auto factors = factorize_compact(i,primes);
        auto divisors_sum = sum_all_divisors(factors);
        if(i < divisors_sum) abundant.push_back(i);
    }

    return abundant;
}

int main() {
	Measure measure;
	const auto &primes = PrimeNumbers(abundant_representable_limit);
	auto passed = measure.passed();
	if(!util::test_mode()) {
		std::cout << "Prime generation took " << passed << " ms" << std::endl;
	}

	measure.reset();
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

    passed = measure.passed();
    if(!util::test_mode()) {
    	std::cout << "Processing took " << passed << " ms" << std::endl;
    	std::cout << "Sum of natural numbers not representable by the sum of two abundant numbers: ";
    }
    std::cout << total << std::endl;
    return 0;
}
