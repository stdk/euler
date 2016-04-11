#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <primes.h>
#include <util.h>

size_t search_pandigital_prime(size_t *digits, size_t len, size_t permutations, const PrimeNumbers &primes) {
	std::reverse_iterator<size_t*> reverse_digits(digits+len);

	for(size_t k=0;k<permutations;k++) {

		size_t n = std::accumulate(reverse_digits,reverse_digits+len,(size_t)0,[](size_t n, size_t digit) {
			return 10*n + digit;
		});

		if(primes[n]) {
			return n;
		}

		std::prev_permutation(reverse_digits,reverse_digits+len);
	}

	return 0;
}



int main() {
	Measure measure;
	const auto &primes = PrimeNumbers(100000);

	auto passed = measure.passed();
	if(!util::test_mode()) {
		std::cout << "Prime generation took: " << passed << " ms" << std::endl;
	}

	const size_t digit_num = 9;
	size_t digits[digit_num];

	size_t permutations = factorial<digit_num>::value;

	measure.reset();
	for(size_t i=digit_num;i>0;i--) {
		std::iota(digits,digits+i,1);
		if(size_t prime = search_pandigital_prime(digits,i,permutations,primes)) {
			if(!util::test_mode()) {
				std::cout << "Pandigital prime search took: " << measure.passed() << " ms" << std::endl;
				std::cout << "Pandigital prime: ";
			}
			std::cout << prime << std::endl;
			break;
		}

		permutations /= i;
	}

	return 0;
}
