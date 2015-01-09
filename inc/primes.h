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

template<class P>
void factorize_compact(uint64_t number, const P &primes, CompactFactors &factors) {
    factors.clear();

    if(number == 1) return;

    for(auto prime: primes) {
    	size_t count = 0;
        while(number % prime == 0) {
            number /= prime;
            count++;
        }
        if(count) {
            factors.push_back(std::make_tuple(prime, count));
            if(number == 1) return;
        }
    }

    if(number > *primes.rbegin()) {
    	factors.push_back(std::make_tuple(number,1));
    }
}

template<class P>
CompactFactors factorize_compact(uint64_t number, const P &primes) {
    CompactFactors factors;
    factorize_compact(number, primes, factors);
    return factors;
}

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
