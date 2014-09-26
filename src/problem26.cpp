#include <iostream>
#include <numeric>
#include <cmath>
#include <gmpxx.h>
#include <primes.h>

size_t reciprocal_cycle_length(size_t prime) {
	mpz_class p = prime;
	mpz_class base = 9_mpz;

	size_t result = 1;
	while(base % p != 0_mpz) {
		base = base*10 + 9;
		++result;
	}

	return result;
}

int main() {
	const auto primes = generate_primes(1000);

	size_t longest_rcp_cycle_number = 0;
	size_t longest_rcp_cycle_length = 0;
	//no need to check 2,3,5 since 2 and 5 are exceptions to our rule for determining reciprocal cycle length
	for(auto p=primes.rbegin();p!=primes.rend()-3;++p) {
		//std::cout << "Checking " << *p << std::endl;
		auto length = reciprocal_cycle_length(*p);
		if(length > longest_rcp_cycle_length) {
			longest_rcp_cycle_length = length;
			longest_rcp_cycle_number = *p;
		}
	}

	std::cout << longest_rcp_cycle_number << " [" << longest_rcp_cycle_length << "]" << std::endl;

	return 0;
}
