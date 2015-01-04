#include <primes.h>
#include <cmath>
#include <iostream>

std::tuple<const Primes, const PrimePresence> generate_primes_state(const size_t limit) {

	// see http://en.wikipedia.org/wiki/Prime-counting_function
	//primes.reserve(1.25506*limit/log(limit));
	//primes.reserve(limit/(log(limit)-1.1));
	std::vector<size_t> primes(limit/(log(limit)-1.1));

	auto prime = primes.begin();
	*prime++ = 2;
	*prime++ = 3;

	// 5 7 11 13 17 19 23 25 29 31 35 37 41 43 47 49 53 55 59 61 65 67 ...
	// 0 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21
	// only numbers of the following form: 6*n - 1, 6*n + 1, n >= 1 can be primes
	std::vector<bool> N(limit/3 + 1, true);

	for(size_t i=1; i < limit/6; i++) {
		if(N[2*i - 2]) {
			const size_t p = 6*i-1;
			const size_t upper = limit/6 + i + 1;
			const size_t lower = limit/6 - i + 1;
			size_t j = p;
			while(j<lower) {
				N[(j-i)*2-1] = false;
				N[(j+i-1)*2] = false;
				j+=p;
			}
			while(j<upper) {
				N[(j-i)*2-1] = false;
				j+=p;
			}
			*prime++ = p;
		}
		if(N[2*i - 1]) {
			const size_t p = 6*i+1;
			const size_t upper = limit/6 + i + 1;
			const size_t lower = limit/6 - i + 1;
			size_t j = p;
			while(j<lower) {
				N[(j-i-1)*2] = false;
				N[(j+i)*2-1] = false;
				j+=p;
			}
			while(j<upper) {
				N[(j-i-1)*2] = false;
				j+=p;
			}
			*prime++ = p;
		}
	}

	primes.resize(prime - primes.begin());

	return std::make_tuple(std::move(primes),std::move(N));
}

const Primes generate_primes_vector(size_t limit) {
    return std::get<0>(generate_primes_state(limit));
}

const PrimePresence generate_primes_presence(const size_t limit) {
	// 5 7 11 13 17 19 23 25 29 31 35 37 41 43 47 49 53 55 59 61 65 67 ...
	// 0 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21
	// only numbers of the following form: 6*n - 1, 6*n + 1, n >= 1 can be primes
	std::vector<bool> N(limit/3 + 1, true);

	const size_t bound = limit/6;

	for(size_t i=1; i < bound; i++) {
		const bool a = N[2*i - 2];
		const bool b = N[2*i - 1];
		if(a && b) {
			const size_t p1 = 6*i-1;
			const size_t p2 = 6*i+1;
			const size_t upper = bound + i + 1;
			const size_t lower = bound - i + 1;
			size_t j1 = p1,j2 = p2;
			while(j1<lower && j2<lower) {
				N[(j1-i)*2-1] = false;
				N[(j1+i-1)*2] = false;

				N[(j2-i-1)*2] = false;
				N[(j2+i)*2-1] = false;

				j1+=p1;
				j2+=p2;
			}

			while(j1<lower && j2<upper) {
				N[(j1-i)*2-1] = false;
				N[(j1+i-1)*2] = false;

				N[(j2-i-1)*2] = false;

				j1+=p1;
				j2+=p2;
			}

			while(j1<upper && j2<lower) {
				N[(j1-i)*2-1] = false;

				N[(j2-i-1)*2] = false;
				N[(j2+i)*2-1] = false;

				j1+=p1;
				j2+=p2;
			}

			while(j1<upper && j2 < upper) {
				N[(j1-i)*2-1] = false;

				N[(j2-i-1)*2] = false;

				j1+=p1;
				j2+=p2;
			}

			while(j1<upper) {
				N[(j1-i)*2-1] = false;
				j1+=p1;
			}

			while(j2<upper) {
				N[(j2-i-1)*2] = false;
				j2+=p2;
			}
		} else if(a) {
			const size_t p = 6*i-1;
			const size_t upper = bound + i + 1;
			const size_t lower = bound - i + 1;
			size_t j = p;
			while(j<lower) {
				N[(j-i)*2-1] = false;
				N[(j+i-1)*2] = false;
				j+=p;
			}
			while(j<upper) {
				N[(j-i)*2-1] = false;
				j+=p;
			}
		} else if(b) {
			const size_t p = 6*i+1;
			const size_t upper = bound + i + 1;
			const size_t lower = bound - i + 1;
			size_t j = p;
			while(j<lower) {
				N[(j-i-1)*2] = false;
				N[(j+i)*2-1] = false;
				j+=p;
			}
			while(j<upper) {
				N[(j-i-1)*2] = false;
				j+=p;
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
