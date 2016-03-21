#include <iostream>
#include <algorithm>
#include <vector>
#include <primes.h>
#include <util.h>

size_t search(const PrimeNumbers &primes, size_t limit) {
	for(size_t i=9;i<limit;i+=2) {
		auto p = std::lower_bound(primes.begin(),primes.end(),i);
		if(*p != i) {
			while(--p != primes.begin()) {
				auto diff = i - *p;
				auto root = perfect_square_root(diff/2);
				if(-1 != root) {
					break;
				}
			}
			if(p == primes.begin()) return i;
		}
	}
	return 0;
}

int main(int argc, char **argv) {
	std::ios_base::sync_with_stdio(false);

	const size_t limit = 1000000;

	Measure measure;
	const auto& primes = PrimeNumbers(limit);
	auto passed = measure.passed();
	std::cout << "Generation of primes took " << passed << " ms" << std::endl;

	measure.reset();
	size_t number = search(primes,limit);
	passed = measure.passed();
	std::cout << "Search of " << number << " took " << passed << " ms" << std::endl;

	return 0;
}
