#include <cppformat/format.h>
#include <primes.h>
#include <algorithm>
#include <fraction.h>
#include <util.h>

auto quotient(uint32_t n, const PrimeNumbers &primes) {
	auto factors = factorize(n, primes);

	uint64_t p = 1;
	uint64_t q = 1;

	for(const auto &factor: factors) {
		p *= factor.prime;
		q *= factor.prime - 1;
	}

	return Fraction<uint64_t>(p,q).simplify();
}

int main(int argc, char **argv) {
	std::ios_base::sync_with_stdio(false);

	if(argc != 2) {
		fmt::print("Usage: {} <limit>\n", argv[0]);
		return 1;
	}

	const uint32_t limit = std::stoi(argv[1]);

	Measure measure;

	const auto &primes = PrimeNumbers(std::max(limit/1000,(uint32_t)1000));

	uint32_t n = 1;
	auto i = primes.begin();
	while(n < limit && i!=primes.end()) {
		n *= *i++;
	}
	n /= *--i;

	auto passed = measure.passed();
	if(!util::test_mode()) {
		fmt::print("Passed: {} ms\n", passed);
		//auto q = quotient(n, primes);
		//fmt::print("[n={}]: n/phi(n) = {} = {}\n", n, q, (double)q.p()/q.q());
	}

	fmt::print("{}\n",n);

	return 0;
}
