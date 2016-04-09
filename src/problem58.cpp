#include <iostream>
#include <cstdint>
#include <primes.h>
#include <util.h>

template<class Primes>
uint32_t search(const Primes &primes) {
	size_t prime_count = 0;
	for(uint32_t n=2;;n++) {
		uint32_t square_size = 2*n - 1;
		uint32_t x = square_size*square_size;
		for(uint32_t i=1;i<4;i++) {
			prime_t candidate = x-i*(2*n-2);

			if(candidate > *primes.rbegin()) {
				return 0;
			}

			if(primes[candidate]) {
				prime_count++;
			}
		}
		uint32_t diagonal_number_count = 4*(n-1)+1;
		if(diagonal_number_count/10 >= prime_count) {
			return square_size;
		}
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	const prime_t limit = 1000000000;

	Measure measure;
	const auto &primes = PrimeNumbers(limit);
	auto passed = measure.passed();
	if(!util::test_mode()) {
		std::cout << "Prime generation took " << passed << " ms" << std::endl;
	}

	measure.reset();
	uint32_t square_size = search(primes);
	passed = measure.passed();

	if(!util::test_mode()) {
		std::cout << "Search took " << passed << " ms" << std::endl;
		std::cout << "Square size = " << square_size << std::endl;
	} else {
		std::cout << square_size << std::endl;
	}

	return 0;
}
