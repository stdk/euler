#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
#include "primes.h"
#include "util.h"

template<size_t N>
struct fact : std::integral_constant<size_t, N*fact<N-1>::value> {};

template<>
struct fact<1> : std::integral_constant<size_t, 1> {};

size_t search_pandigital_prime(size_t *digits, size_t len, size_t permutations, const std::vector<bool> &presence) {
	std::reverse_iterator<size_t*> reverse_digits(digits+len);

	for(size_t k=0;k<permutations;k++) {

		size_t n = std::accumulate(reverse_digits,reverse_digits+len,(size_t)0,[](size_t n, size_t digit) {
			return 10*n + digit;
		});

		if(prime_present(n,presence)) {
			return n;
		}

		std::prev_permutation(reverse_digits,reverse_digits+len);
	}

	return 0;
}



int main(int argc, char **argv) {
	Measure measure;
	const std::vector<bool> &presence = generate_primes_presence(1000000000);
	//const auto primes_state = generate_primes_state(1000000000);
	//const auto& presence = std::get<1>(primes_state);

	auto passed = measure.passed();
	std::cout << "Prime generation took: " << passed << " ms" << std::endl;

	const size_t digit_num = 9;
	size_t digits[digit_num];

	size_t permutations = fact<digit_num>::value;

	measure.reset();
	for(size_t i=digit_num;i>0;i--) {
		std::iota(digits,digits+i,1);
		if(size_t prime = search_pandigital_prime(digits,i,permutations,presence)) {
			std::cout << "Pandigital prime search took: " << measure.passed() << " ms" << std::endl;
			std::cout << "Pandigital prime: " << prime << std::endl;
			break;
		}

		permutations /= i;
	}

	return 0;
}