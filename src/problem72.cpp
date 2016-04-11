#include <cppformat/format.h>
#include <cstdint>
#include <cmath>
#include <primes.h>
#include <util.h>

uint32_t totient(uint32_t n, const PrimeNumbers &primes) {
	const auto &factors = factorize(n, primes);

	uint32_t t = 1;

	for(const auto &factor: factors) {
		t *= factor.prime - 1;
		for(auto i=factor.count-1;i;--i) {
			t *= factor.prime;
		}
	}

	return t;
}

int main(int argc, char **argv) {
	std::ios_base::sync_with_stdio(false);

	if(argc != 2) {
		fmt::print("Usage: {} <max denominator>\n", argv[0]);
		return 1;
	}

	const prime_t limit = std::stoul(argv[1]);

	const auto &primes = PrimeNumbers(std::sqrt(limit)+1);

	uint64_t sum = 0;

	for(uint32_t i=2;i<=limit;++i) {
		sum += totient(i, primes);
	}

	fmt::print("{}\n", sum);

	return 0;
}
