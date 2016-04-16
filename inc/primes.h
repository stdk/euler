#ifndef PRIMES_H
#define PRIMES_H

#include <vector>
#include <cstddef>
#include <cstdint>
#include <tuple>

typedef uint32_t prime_t;

struct Factor {
    prime_t prime;
    size_t count;

    Factor(prime_t p, size_t c):prime(p),count(c) {

    }

    size_t product() const {
        size_t p = prime;
        for(size_t i=0;i<count-1;++i) {
            p *= prime;
        }
        return p;
    }
};

typedef std::vector<prime_t> Primes;
typedef std::vector<Factor> Factors;
typedef std::vector<bool> PrimePresence;

PrimePresence generate_primes_presence(prime_t limit);
bool prime_present(prime_t number, const PrimePresence &presence);

class PrimeNumbers
{
    prime_t m_limit;
    prime_t m_detect_limit;

    Primes primes;
    PrimePresence presence;
public:
    PrimeNumbers(prime_t limit);

    prime_t limit() const {
        return m_limit;
    }

    prime_t detect_limit() const {
        return m_detect_limit;
    }

    typedef decltype(primes.begin()) iterator;
    typedef decltype(primes.cbegin()) const_iterator;

    inline auto begin() {
        return primes.begin();
    }

    inline auto begin() const {
        return primes.begin();
    }

    inline auto end() {
        return primes.end();
    }

    inline auto end() const {
        return primes.end();
    }

    inline auto rbegin() {
        return primes.rbegin();
    }

    inline auto rbegin() const {
        return primes.rbegin();
    }

    inline auto rend() {
        return primes.rend();
    }

    inline auto rend() const {
        return primes.rend();
    }

    bool operator[](prime_t number) const;

    bool exclude_prime(prime_t number);
};

void factorize(uint64_t number, const PrimeNumbers &primes, Factors &factors, bool cutoff=false);
Factors factorize(uint64_t number, const PrimeNumbers &primes, bool cutoff=false);

Factors common_factors(const Factors &a,
                       const Factors &b);

Factors common_factors(const Factors &a,
                       const Factors &b,
                       const Factors &c);

std::ostream& operator<<(std::ostream &os, const Factor &factor);
std::ostream& operator<<(std::ostream &os, const Factors &factors);

#endif //PRIMES_H
