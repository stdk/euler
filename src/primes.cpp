#include <primes.h>
#include <cmath>
#include <iostream>

std::tuple<const Primes, const std::vector<bool>> generate_primes_state(size_t limit) {
	std::vector<bool> N(limit/2 + 1, true); // 3 5 7 9 11 ...

	std::vector<size_t> primes;

	// see http://en.wikipedia.org/wiki/Prime-counting_function
	//primes.reserve(1.25506*limit/log(limit));
	primes.reserve(limit/(log(limit)-1.1));

	primes.push_back(2);

	for(size_t i=3; i < limit; i+=2) {
		if(N[i/2 - 1]) {
			for(size_t j=3*i;j<limit;j+=2*i) {
				N[j/2 - 1] = false;
			}
			primes.push_back(i);
		}
	}

	return std::make_tuple(std::move(primes),std::move(N));
}

const Primes generate_primes_vector(size_t limit) {
    return std::get<0>(generate_primes_state(limit));
}

const std::vector<bool> generate_primes_presence(size_t limit) {
	std::vector<bool> N(limit/2 + 1, true); // 3 5 7 9 11 ...

	for(size_t i=3; i < limit; i+=2) {
		if(N[i/2 - 1]) {
			for(size_t j=3*i;j<limit;j+=2*i) {
				N[j/2 - 1] = false;
			}
		}
	}

	return N;
}

std::size_t sum_primes(std::size_t limit) {
    std::vector<bool> N(limit / 2, true); // 3 5 7 9 11 ...
    size_t sum = 2;
    
    for(size_t i=3; i < limit; i+=2) {
        if(N[i/2 - 1]) {
            for(size_t j=3*i;j<limit;j+=2*i) {
                N[j/2 - 1] = false;   
            }
            sum += i;
        }
    }
    
    return sum;    
}

bool factorize(size_t number, const Primes &primes, Factors &factors) {
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

Factors factorize(size_t number, const Primes &primes) {
    Factors factors;
    factorize(number, primes, factors);
    return factors;    
}

bool factorize_compact(size_t number, const Primes &primes, CompactFactors &factors) {
    factors.clear();
    
    if(number == 1) {
        return true;
    }
    
    for(auto prime: primes) {
        size_t count = 0;
        while(number % prime == 0) {
            number /= prime;
            count++;
        }
        if(count) {
            factors.push_back(std::make_tuple(prime, count));
            if(number == 1) {
                return true;
            }
        }
    }
    
    return false;
}

CompactFactors factorize_compact(size_t number, const Primes &primes) {
    CompactFactors factors;
    factorize_compact(number, primes, factors);
    return factors;    
}
