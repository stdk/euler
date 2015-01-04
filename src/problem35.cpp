#include <iostream>
#include <primes.h>

size_t digit_count(size_t number, size_t base=10) {
	size_t count = 0;
	while(number) {
		++count;
		number /= base;
	}
	return count;
}

size_t circular_shift(size_t number, size_t digits, size_t base=10) {
	size_t high = 1;
	while(--digits) high*=base;
	return high*(number % base) + number / 10;
}

template<class Presence>
bool is_circular(size_t prime, Presence presence) {
	size_t digits = digit_count(prime);

	for(size_t i=0;i<digits-1;i++) {
		prime = circular_shift(prime,digits);
		if(!prime_present(prime,presence)) return false;
	}

	return true;
}

int main() {
	const auto primes_state = generate_primes_state(1000000);
	const auto& primes = std::get<0>(primes_state);
	const auto& presence = std::get<1>(primes_state);

	size_t count = 0;

	for(auto i: primes) {
		if(is_circular(i,presence)) {
			++count;
			std::cout << i << std::endl;
		}
	}

	std::cout << "Count: " << count << std::endl;

	return 0;
}
