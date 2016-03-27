#ifndef PRIMES_H
#define PRIMES_H

#include <vector>
#include <cstddef>
#include <cstdint>
#include <tuple>

typedef uint32_t prime_t;

typedef std::vector<prime_t> Primes;
typedef std::vector<prime_t> Factors;
typedef std::tuple<prime_t, prime_t> CompactFactor;
typedef std::vector<CompactFactor> CompactFactors;
typedef std::vector<bool> PrimePresence;

PrimePresence generate_primes_presence(prime_t limit);
bool prime_present(prime_t number, const PrimePresence &presence);

class PrimeNumbers
{
	Primes primes;
	PrimePresence presence;
public:
	PrimeNumbers(prime_t limit);

	inline auto begin() -> decltype(primes.begin()) {
		return primes.begin();
	}

	inline auto begin() const -> decltype(primes.begin()) {
		return primes.begin();
	}

	inline auto end() -> decltype(primes.end()) {
		return primes.end();
	}

	inline auto end() const -> decltype(primes.end()) {
		return primes.end();
	}

	inline auto rbegin() -> decltype(primes.rbegin()) {
		return primes.rbegin();
	}

	inline auto rbegin() const -> decltype(primes.rbegin()) {
		return primes.rbegin();
	}

	inline auto rend() -> decltype(primes.rend()) {
		return primes.rend();
	}

	inline auto rend() const -> decltype(primes.rend()) {
		return primes.rend();
	}

	bool operator[](prime_t number) const;

	bool exclude_prime(prime_t number);
};

bool factorize(prime_t number, const PrimeNumbers &primes, Factors &factors);
Factors factorize(prime_t number, const PrimeNumbers &primes);

void factorize_compact(uint64_t number, const PrimeNumbers &primes, CompactFactors &factors);
CompactFactors factorize_compact(uint64_t number, const PrimeNumbers &primes);

CompactFactors common_compact_factors(const CompactFactors &a, const CompactFactors &b);
CompactFactors common_compact_factors(const CompactFactors &a,
                                      const CompactFactors &b,
                                      const CompactFactors &c);

std::ostream& operator<<(std::ostream &os, const CompactFactor &factor);
std::ostream& operator<<(std::ostream &os, const CompactFactors &factors);

#endif //PRIMES_H
