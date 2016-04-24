#include <primes.h>
#include <cmath>
#include <algorithm>
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

bool PrimeNumbers::operator[](prime_t number) const {
    if(number < m_limit) {
        return prime_present(number,presence);
    }

    if(number < m_detect_limit) {
        for(auto prime: primes) {
            if(number % prime == 0) {
                return false;
            }
        }
        return true;
    }

    return false;
}

bool PrimeNumbers::exclude_prime(prime_t number) {
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

PrimeNumbers::PrimeNumbers(prime_t limit):
m_limit(std::max((prime_t)4,limit)),
m_detect_limit(m_limit*m_limit),

// see http://en.wikipedia.org/wiki/Prime-counting_function
//primes(1.25506*limit/log(limit));
//primes(limit/(log(limit)-1.1));
primes(m_limit/(log(m_limit)-1.1)),

// 5 7 11 13 17 19 23 25 29 31 35 37 41 43 47 49 53 55 59 61 65 67 ...
// 0 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21
// only numbers of the following form: 6*n - 1, 6*n + 1, n >= 1 can be primes
presence(m_limit/3 + 2, true) {
    auto prime = primes.begin();
    *prime++ = 2;
    *prime++ = 3;

    const prime_t bound = m_limit/3;
    const prime_t iteration_limit = sqrt(m_limit)/6 + 1;

    prime_t i = 0;
    prime_t i2 = 0;
    prime_t a = 5;
    prime_t b = 7;
    for(;i < iteration_limit;i2+=2*i+1, i++, a+=6, b+=6) {
        if(presence[2*i]) {
            *prime++ = a;
            const prime_t diff = 2*a;
            prime_t j1 = (3*i2 + 5*i + 2)*4-1;
            prime_t j2 = j1 + 4*(i+1) - 1;
            for(;j2 < bound;j1+=diff,j2+=diff) {
                presence[j1] = false;
                presence[j2] = false;
            }
            for(;j1 < bound;j1+=diff) {
                presence[j1] = false;
            }
        }
        if(presence[2*i + 1]) {
            *prime++ = b;
            const prime_t diff = 2*b;
            prime_t j2 = (3*i2 + 7*i + 4)*4-1;
            prime_t j1 = j2 - 4*(i+1) - 1;
            for(;j2 < bound;j1+=diff,j2+=diff) {
                presence[j1] = false;
                presence[j2] = false;
            }
            for(;j1 < bound;j1+=diff) {
                presence[j1] = false;
            }

        }
    }

    for(;i<m_limit/6+1;i++,a+=6,b+=6) {
        if(presence[2*i]) {
            *prime++ = a;
        }
        if(presence[2*i + 1]) {
            *prime++ = b;
        }
    }

    for(;*(prime-1) > limit;--prime);

    primes.resize(prime - primes.begin());
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

Factors common_factors(const Factors &a, const Factors &b) {
    Factors common_factors;

    auto i = a.begin();
    auto j = b.begin();

    while(i!=a.end() && j != b.end()) {

        auto x = i->prime;
        auto y = j->prime;

        if(x == y) {
            auto count = std::min(i->count,j->count);
            common_factors.emplace_back(x,count);
            ++i;
            ++j;
        } else if(x < y) {
            ++i;
        } else if(x > y) {
            ++j;
        }

    }

    return common_factors;
}

Factors common_factors(const Factors &a,
                               const Factors &b,
                               const Factors &c) {
    Factors common_factors;

    auto i = a.begin();
    auto j = b.begin();
    auto k = c.begin();

    while(i != a.end() && j != b.end() && k != c.end()) {
        auto x = i->prime;
        auto y = j->prime;
        auto z = k->prime;

        if(x == y && y == z) {
            auto count = std::min({i->count,
                                   j->count,
                                   k->count});
            common_factors.emplace_back(x,count);
            ++i;
            ++j;
            ++k;
        } else if(x <= y && x <= z) {
            ++i;
        } else if(y <= x && y <= z) {
            ++j;
        } else if(z <= x && z <= y) {
            ++k;
        }
    }

    return common_factors;
}

void factorize(uint64_t number, const PrimeNumbers &primes, Factors &factors, bool cutoff) {
    factors.clear();

    if(number <= 1) return;

    for(auto prime: primes) {
        size_t count = 0;
        while(number % prime == 0) {
            number /= prime;
            count++;
        }
        if(count) {
            factors.emplace_back(prime, count);
            if(number == 1) return;
        }

        if(cutoff && number < primes.limit() && primes[number]) break;
    }

      factors.emplace_back(number,1);
}

Factors factorize(uint64_t number, const PrimeNumbers &primes, bool cutoff) {
    Factors factors;
    factorize(number, primes, factors, cutoff);
    return factors;
}

std::ostream& operator<<(std::ostream &os, const Factor &factor) {
    return os << factor.prime << "^" << factor.count;
}

std::ostream& operator<<(std::ostream &os, const Factors &factors) {
    os << "[";
    for(auto i=factors.begin();i!=factors.end();++i) {
        os << *i << (i == factors.end()-1 ? "" : " * ");
    }
    os << "]";

    return os;
}
