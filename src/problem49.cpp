#include <iostream>
#include <sstream>
#include <algorithm>
#include <primes.h>
#include <util.h>
#include <cstdint>
#include <bitset>

bool next_digit_permutation(uint32_t &number) {
    if(!number) return false; // no elements
    if(number < 10) return false; // single element

    uint32_t pivot = number % 10;
    uint32_t front = number / 10;
    uint32_t order = 10;

    while(pivot <= front%10) {
        pivot = front%10;
        front /= 10;
        order *= 10;

        if(!front) { // last permutation already
            number = reverse_digits(number);
            return false;
        }
    }
    pivot = front%10;

    uint32_t mid = number - front*order;
    uint32_t mfront = mid;
    uint32_t morder = 1;

    while(mfront%10 <= pivot) {
        mfront /= 10;
        morder *= 10;
    }

    front = front - pivot + mfront%10;
    uint32_t back = mid - mfront*morder;
    mfront = (mfront - mfront%10 + pivot)*morder + back;

    number = front*order + reverse_digits(mfront);

    return true;
}

template<class Sequence>
bool is_correct_sequence(Sequence &sequence) {
    if(sequence.size() < 3) return false;

    uint32_t mask = (1 << sequence.size()) - 1;
    uint32_t combination = 0b111;

    Sequence c(3);

    while(next_combination(combination,mask)) {
        auto i = c.begin();
        uint32_t x = combination;
        while(uint32_t k = __builtin_ffs(x)) {
            *i++ = sequence[k-1];
             x &= ~(1 << (k-1));
        }

        if(c[1]-c[0] == c[2]-c[1]) {
            sequence = c;
            return true;
        }
    }

    return false;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    const uint64_t limit = 10000;

    Measure measure;

    auto primes = PrimeNumbers(limit);

    auto passed = measure.passed();
    if(!util::test_mode()) {
        std::cout << "Prime generation took: " << passed << " ms" << std::endl;
    }

    auto begin = std::lower_bound(primes.begin(),primes.end(),1000);
    auto end = std::lower_bound(primes.begin(),primes.end(),10000);

    std::vector<uint32_t> sequence;

    std::string result;

    measure.reset();
    for(auto i=begin;i!=end;++i) {
        uint32_t prime = *i;
        if(primes.exclude_prime(prime)) {
            sequence.clear();
            sequence.push_back(prime);

            size_t primes_in_permutations = 1;
            while(next_digit_permutation(prime)) {
                if(primes.exclude_prime(prime)) {
                    primes_in_permutations += 1;
                    sequence.push_back(prime);
                }
            }

            if(is_correct_sequence(sequence)) {
                std::ostringstream os;
                for(auto p: sequence) {
                    os << p;
                }
                result = os.str();
            }
        }
    }
    passed = measure.passed();

    if(!util::test_mode()) {
        std::cout << "Search took: " << passed << " ms" << std::endl;
    }

    std::cout << result << std::endl;

    return 0;
}

