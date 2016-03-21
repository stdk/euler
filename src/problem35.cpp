#include <iostream>
#include <primes.h>
#include <util.h>

size_t circular_shift(size_t number, size_t digits, size_t base=10) {
	size_t high = 1;
	while(--digits) high*=base;
	return high*(number % base) + number / 10;
}

template<class Presence>
bool is_circular(size_t prime, const Presence &presence) {
	size_t digits = digit_count(prime);

	for(size_t i=0;i<digits-1;i++) {
		prime = circular_shift(prime,digits);
		if(!presence[prime]) return false;
	}

	return true;
}

int main() {
	const auto &primes = PrimeNumbers(1000000);

	size_t count = 0;

	for(auto i: primes) {
		if(is_circular(i,primes)) {
			++count;
			std::cout << i << std::endl;
		}
	}

	std::cout << "Count: " << count << std::endl;

	return 0;
}
