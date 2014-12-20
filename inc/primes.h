#ifndef PRIMES_H
#define PRIMES_H

#include <vector>
#include <cstddef>
#include <tuple>

typedef std::vector<std::size_t> Primes;
typedef std::vector<std::size_t> Factors;
typedef std::tuple<std::size_t, std::size_t> CompactFactor;
typedef std::vector<CompactFactor> CompactFactors;

std::tuple<const Primes, const std::vector<bool>> generate_primes_state(std::size_t limit);
const std::vector<std::size_t> generate_primes_vector(std::size_t limit);
const std::vector<bool> generate_primes_presence(std::size_t limit);

std::size_t sum_primes(std::size_t limit);

inline bool prime_present(std::size_t number, const std::vector<bool> &presence) {
	if(number == 2) return true;
	if(number < 2 || number % 2 == 0) return false;
	return presence[number/2 - 1];
}

bool factorize(size_t number, const Primes &primes, Factors &factors);

std::vector<std::size_t> factorize(std::size_t number, const Primes &primes);

std::vector< std::tuple<size_t, size_t> > factorize_compact(size_t number, const Primes &primes);

bool factorize_compact(size_t number, const Primes &primes, CompactFactors &factors);

#endif
