#ifndef PRIMES_H
#define PRIMES_H

#include <vector>
#include <cstddef>
#include <tuple>

typedef std::vector<std::size_t> Primes;
typedef std::vector<std::size_t> Factors;
typedef std::tuple<std::size_t, std::size_t> CompactFactor;
typedef std::vector<CompactFactor> CompactFactors;
typedef std::vector<bool> PrimePresence;

std::tuple<const Primes, const PrimePresence> generate_primes_state(std::size_t limit);
const std::vector<std::size_t> generate_primes_vector(std::size_t limit);
const PrimePresence generate_primes_presence(const std::size_t limit);

std::size_t sum_primes(std::size_t limit);

inline bool prime_present(std::size_t number, const std::vector<bool> &presence) {
	if(number < 2) return false;
	if(number < 4) return true;
	size_t remainder = number % 6;
	if(5 == remainder) {
		return presence[number/6*2];
	} else if(1 == remainder) {
		return presence[number/6*2-1];
	} else {
		return false;
	}
}

bool factorize(size_t number, const Primes &primes, Factors &factors);

std::vector<std::size_t> factorize(std::size_t number, const Primes &primes);

CompactFactors factorize_compact(size_t number, const Primes &primes);
bool factorize_compact(size_t number, const Primes &primes, CompactFactors &factors);

#endif
