#include <iostream>
#include <algorithm>
#include <primes.h>
#include <util.h>

int main(int argc, char ** argv) {
	std::ios_base::sync_with_stdio(false);

	Measure measure;
	const prime_t limit = 1000000;
	const auto &primes = PrimeNumbers(limit);
	auto passed = measure.passed();
	std::cout << "Prime generation took: " << passed << " ms" << std::endl;

	measure.reset();
	prime_t sum = *primes.begin();
	auto begin = primes.begin();
	auto last_success = primes.begin();
	size_t best_length = 1;
	for(auto i=begin+1;begin <= last_success && i!=primes.end();i++) {
		sum += *i;
		size_t length = i - begin + 1;
		if(primes[sum] && length > best_length) {
			best_length = length;
			last_success = i;
			std::cout << sum << " " << length << std::endl;
		}
		if(sum > *primes.rbegin()) {
			for(;i!=last_success;--i) {
				sum -= *i;
			}
			sum -= *begin++;
		}
	}
	passed = measure.passed();
	std::cout << "Search took: " << passed << " ms" << std::endl;

	return 0;
}
