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

#endif
