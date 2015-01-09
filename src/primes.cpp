#include <primes.h>
#include <cmath>
#include <iostream>

bool prime_present(prime_t number, const PrimePresence &presence) {
	if(number < 2) return false;
	if(number < 4) return true;
	if(number/6*2>presence.size()) return false;
	prime_t remainder = number % 6;
	if(5 == remainder) {
		return presence[number/6*2];
	} else if(1 == remainder) {
		return presence[number/6*2-1];
	} else {
		return false;
	}
}

bool exclude_prime(prime_t number, PrimePresence &presence) {
	if(number < 2) return false;
	if(number < 4) return false;
	if(number/6*2>presence.size()) return false;
	prime_t remainder = number % 6;
	if(5 == remainder) {
		if(presence[number/6*2]) {
			presence[number/6*2] = false;
			return true;
		}
	} else if(1 == remainder) {
		if(presence[number/6*2-1]) {
			presence[number/6*2-1] = false;
			return true;
		}
	}
	return false;
}

std::tuple<Primes, PrimePresence> generate_primes_state(prime_t limit) {

	// see http://en.wikipedia.org/wiki/Prime-counting_function
	//primes.reserve(1.25506*limit/log(limit));
	//primes.reserve(limit/(log(limit)-1.1));
	Primes primes(limit/(log(limit)-1.1));

	auto prime = primes.begin();
	*prime++ = 2;
	*prime++ = 3;

	// 5 7 11 13 17 19 23 25 29 31 35 37 41 43 47 49 53 55 59 61 65 67 ...
	// 0 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21
	// only numbers of the following form: 6*n - 1, 6*n + 1, n >= 1 can be primes
	PrimePresence N(limit/3 + 1, true);

	const prime_t bound = limit/3;
	const prime_t iteration_limit = sqrt(limit)/6 + 1;
	prime_t i = 1;
	for(;i < iteration_limit; i++) {
		if(N[2*i - 2]) {
			const prime_t p = 6*i-1;
			const prime_t diff = 2*p;
			prime_t j1 = p*p/6*2 - 1;
			prime_t j2 = j1 + 4*i - 1;
			for(;j2 < bound;j1+=diff,j2+=diff) {
				N[j1] = false;
				N[j2] = false;
			}
			for(;j1 < bound;j1+=diff) {
				N[j1] = false;
			}
			*prime++ = p;
		}
		if(N[2*i - 1]) {
			const prime_t p = 6*i+1;
			const prime_t diff = 2*p;
			prime_t j2 = p*p/6*2 - 1;
			prime_t j1 = j2 - 4*i - 1;
			for(;j2 < bound;j1+=diff,j2+=diff) {
				N[j1] = false;
				N[j2] = false;
			}
			for(;j1 < bound;j1+=diff) {
				N[j1] = false;
			}
			*prime++ = p;
		}
	}

	for(;i<limit/6+1;i++) {
		if(N[2*i - 2]) {
			const prime_t p = 6*i-1;
			*prime++ = p;
		}
		if(N[2*i - 1]) {
			const prime_t p = 6*i+1;
			*prime++ = p;
		}
	}

	primes.resize(prime - primes.begin());

	return std::make_tuple(std::move(primes),std::move(N));
}

Primes generate_primes_vector(prime_t limit) {
    return std::get<0>(generate_primes_state(limit));
}

PrimePresence generate_primes_presence(prime_t limit) {
	// 5 7 11 13 17 19 23 25 29 31 35 37 41 43 47 49 53 55 59 61 65 67 ...
	// 0 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21
	// only numbers of the following form: 6*n - 1, 6*n + 1, n >= 1 can be primes
	PrimePresence N(limit/3 + 1, true);

	const prime_t bound = limit/3;
	const prime_t iteration_limit = sqrt(limit)/6 + 1;
	for(prime_t i = 1;i < iteration_limit; i++) {
		if(N[2*i - 2]) {
			const prime_t p = 6*i-1;
			const prime_t diff = 2*p;
			prime_t j1 = p*p/6*2 - 1;
			prime_t j2 = j1 + 4*i - 1;
			for(;j2 < bound;j1+=diff,j2+=diff) {
				N[j1] = false;
				N[j2] = false;
			}
			for(;j1 < bound;j1+=diff) {
				N[j1] = false;
			}
		}
		if(N[2*i - 1]) {
			const prime_t p = 6*i+1;
			const prime_t diff = 2*p;
			prime_t j2 = p*p/6*2 - 1;
			prime_t j1 = j2 - 4*i - 1;
			for(;j2 < bound;j1+=diff,j2+=diff) {
				N[j1] = false;
				N[j2] = false;
			}
			for(;j1 < bound;j1+=diff) {
				N[j1] = false;
			}
		}
	}

	return N;
}

bool factorize(prime_t number, const Primes &primes, Factors &factors) {
    factors.clear();
    
    if(number == 1) {
        return true;
    }
    
    for(auto prime: primes) {
        while(number % prime == 0) {
            factors.push_back(prime);
            number /= prime;
            if(number == 1) return true;
        }
    }
    
    return false;
}

Factors factorize(prime_t number, const Primes &primes) {
    Factors factors;
    factorize(number, primes, factors);
    return factors;    
}
