#include <iostream>
#include <numeric>
#include <cmath>
#include <algorithm>
#include <primes.h>

size_t sequential_primes_length(const Primes &primes, int a, size_t b) {
	auto f = [&](size_t n) -> int {
		return a*n + n*n + b;
	};

	size_t n = 0;
	//while(std::binary_search(primes.begin(),primes.end(),f(n++)));
	while(true) {
		auto x = static_cast<size_t>(f(n));
		auto is_prime = binary_search(primes.begin(),primes.end(),x);
		//std::cout << "f(" << n << ") = " << x << " (" << is_prime << ")" << std::endl;
		n++;
		if(!is_prime) break;
	}

	return n - 1;
}

int main() {
	const auto primes = generate_primes_vector(1000000);
	auto primes_b = generate_primes_vector(1000);
	primes_b.push_back(1);

	long int a_best = 0;
	long int b_best = 0;
	size_t longest_sequence = 0;
	for(auto b=primes_b.begin()+1;b!=primes_b.end();++b) {
		for(int a = -999;a<1000;a+=2) {
			auto length = sequential_primes_length(primes,a,*b);
			if(length > longest_sequence) {
				longest_sequence = length;
				a_best = a;
				b_best = *b;
				//std::cout << "Checking b=" << *b << ", a=" << a << " -> " << length << std::endl;
			}
		}
	}

	std::cout << "a = " << a_best << " | " << "b = " << b_best << " | length = " << longest_sequence << std::endl;
	std::cout << "Product: " << a_best*b_best << std::endl;

	return 0;
}
