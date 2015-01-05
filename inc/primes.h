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

std::tuple<Primes, PrimePresence> generate_primes_state(prime_t limit);
Primes generate_primes_vector(prime_t limit);
PrimePresence generate_primes_presence(prime_t limit);

bool prime_present(prime_t number, const PrimePresence &presence);
bool exclude_prime(prime_t number, PrimePresence &presence);

bool factorize(prime_t number, const Primes &primes, Factors &factors);
Factors factorize(prime_t number, const Primes &primes);

CompactFactors factorize_compact(prime_t number, const Primes &primes);
bool factorize_compact(prime_t number, const Primes &primes, CompactFactors &factors);

class PrimeNumbers
{
	std::tuple<Primes, PrimePresence> state;
public:
	PrimeNumbers(prime_t limit):state(generate_primes_state(limit)) {

	}

	auto begin() -> decltype(std::get<0>(state).begin()) {
		return std::get<0>(state).begin();
	}

	auto begin() const -> decltype(std::get<0>(state).begin()) {
		return std::get<0>(state).begin();
	}

	auto end() -> decltype(std::get<0>(state).end()) {
		return std::get<0>(state).end();
	}

	auto end() const -> decltype(std::get<0>(state).end()) {
		return std::get<0>(state).end();
	}

	auto rbegin() -> decltype(std::get<0>(state).rbegin()) {
		return std::get<0>(state).rbegin();
	}

	auto rbegin() const -> decltype(std::get<0>(state).rbegin()) {
		return std::get<0>(state).rbegin();
	}

	auto rend() -> decltype(std::get<0>(state).rend()) {
		return std::get<0>(state).rend();
	}

	auto rend() const -> decltype(std::get<0>(state).rend()) {
		return std::get<0>(state).rend();
	}

	bool operator[](prime_t number) const {
		return prime_present(number,std::get<1>(state));
	}
};

#endif
