#include <iostream>
#include <primes.h>
#include <util.h>

size_t truncate_right(size_t prime) {
	return prime / 10;
}

size_t truncate_left(size_t prime) {
	size_t rank = 10;
	size_t remainder = 0;
	while(prime / rank) {
		remainder = prime % rank;
		rank *= 10;
	}
	return remainder;
}

template<class T>
bool is_truncatable_prime(size_t prime, const T &presence) {
	size_t p = prime;
	while(p) {
		if(!presence[p]) return false;
		p = truncate_right(p);
	}

	p = prime;
	while(p) {
		if(!presence[p]) return false;
		p = truncate_left(p);
	}

	return true;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	const auto &primes = PrimeNumbers(1000000);

	size_t sum = 0;

	for(auto i=primes.rbegin();i!=primes.rend();++i) {
		if(*i > 10 && is_truncatable_prime(*i,primes)) {
			sum += *i;
		}
	}

	std::cout << sum << std::endl;

	return 0;
}
