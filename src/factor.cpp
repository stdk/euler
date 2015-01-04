#include <iostream>
#include <sstream>
#include <cstdint>
#include <primes.h>
#include <util.h>

int main(int argc, char **argv) {
	std::ios_base::sync_with_stdio(false);
	if(argc < 2) {
		std::cerr << "Please specify a number to factorize." << std::endl;
		return 1;
	}

	std::istringstream in(argv[1]);
	uint32_t number;
	in >> number;

	Measure measure;

	const size_t limit = number/2 + 1;
	const auto primes_state = generate_primes_state(limit);
	const auto& primes = std::get<0>(primes_state);

	auto passed = measure.passed();
	std::cout << "Prime generation up to " << limit << " took: " << passed << " ms" << std::endl;

	CompactFactors factors;
	if(factorize_compact(number,primes,factors)) {
		for(auto factor: factors) {
			for(size_t i=0;i<std::get<1>(factor);i++) {
				std::cout << std::get<0>(factor) << " ";
			}
		}
		std::cout << std::endl;
		return 0;
	} else {
		std::cout << number << std::endl;
		return 2;
	}

	return 0;
}
