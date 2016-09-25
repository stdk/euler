#include <numeric>
#include <cppformat/format.h>
#include <gmpxx.h>
#include <util.h>
#include <continued_fractions.h>

class e_terms_iterator {
    uint32_t n = 0;
public:
    e_terms_iterator(uint32_t _n=0):n(_n)  {

    }

    inline e_terms_iterator& operator++() noexcept {
        ++n;
        return *this;
    }

    inline e_terms_iterator operator++(int) noexcept {
        e_terms_iterator tmp(*this);
        operator++();
        return tmp;
    }

    inline e_terms_iterator& operator--() noexcept {
        --n;
        return *this;
    }

    inline e_terms_iterator operator--(int) noexcept {
        e_terms_iterator tmp(*this);
        operator--();
        return tmp;
    }

    inline e_terms_iterator operator+(int32_t x) noexcept {
        if(x < 0 && std::abs(x) > n) {
            return e_terms_iterator(0);
        }
        return e_terms_iterator(n+x);
    }

    inline e_terms_iterator operator-(int32_t x) noexcept {
        if(x > 0 && std::abs(x) > n) {
            return e_terms_iterator(0);
        }
        return e_terms_iterator(n-x);
    }

    inline bool operator<(const e_terms_iterator &other) noexcept{
        return n < other.n;
    }

    inline bool operator>(const e_terms_iterator &other) noexcept{
        return n > other.n;
    }

    inline bool operator<=(const e_terms_iterator &other) noexcept{
        return n <= other.n;
    }

    inline bool operator>=(const e_terms_iterator &other) noexcept{
        return n >= other.n;
    }

    inline bool operator==(const e_terms_iterator &other) noexcept{
        return n == other.n;
    }

    inline bool operator!=(const e_terms_iterator &other) noexcept{
        return n != other.n;
    }

    inline uint32_t operator*() const noexcept {
        if(0 == n) {
            return 2;
        } else {
            switch(n % 3) {
            case 0:
            case 1:
                return 1;
            case 2:
                return (n/3+1)*2;
            }
        }
        return 0;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);

    Measure measure;

    auto approximation = approximation_iterator<mpz_class>(e_terms_iterator());
    approximation += 99; //to get 100th approximation

    auto str = approximation->p().get_str();
    auto sum = std::accumulate(str.begin(), str.end(), (size_t)0, [](size_t a, size_t b) {
        return a + b - 0x30;
    });

    auto passed = measure.passed();

    if(!util::test_mode()) {
        fmt::print("Processing toook {} ms\n", passed);
        fmt::print("Digit sum in final approximation: ");
    }
    fmt::print("{}\n",sum);

    return 0;
}
