#include <cppformat/format.h>
#include <string>
#include <array>
#include <algorithm>
#include <cmath>
#include <primes.h>
#include <fraction.h>

typedef decltype(std::declval<const PrimeNumbers&>().begin()) component_t;
typedef std::vector<component_t> Components;

auto quotient(const Components &components) {
    uint32_t phi = 1;
    uint32_t n = 1;

    for(auto factor: components) {
        phi *= *factor - 1;
        n   *= *factor;
    }

    return Fraction<uint64_t>(n,phi);
}

bool is_permuted_pair(uint32_t a, uint32_t b) {
    std::array<int8_t,10> digit_count = {0};

    for(;a;a/=10) {
        ++digit_count[a%10];
    }

    for(;b;b/=10) {
        --digit_count[b%10];
    }

    for(auto i: digit_count) {
        if(i) return false;
    }

    return true;
}

auto initial_candidate(uint32_t limit, const PrimeNumbers &primes) {
    return std::lower_bound(primes.begin(),primes.end(),(prime_t)std::sqrt(limit)) - 1;
}

Components next(const Components &components, component_t initial, uint32_t limit, const PrimeNumbers &primes) {
    Components c = components;

//    if(initial - c[1] < 100) {
//        --c[1];
//        return c;
//    }
//
//    ++c[0];
//    c[1] = std::lower_bound(primes.begin(),primes.end(),limit/(*c[0])) - 1;

    ++c[1];

    if(c[1] != primes.end() && *c[0]**c[1] < limit) {
        return c;
    }

    if(c[0] == primes.begin()) {
        return Components{};
    }

    --c[0];

    //double k = 1.0007 / (*c[0]/(*c[0]-1));
    //c[1] = std::lower_bound(primes.begin(),primes.end(),k/(k-1))-1;
    c[1] = initial;

    return c;
}

auto search(uint32_t limit, const PrimeNumbers &primes) {
    const size_t iteration_limit = 10000;

    auto initial = initial_candidate(limit, primes);
    Components components = {initial, initial};

    for(size_t i=0;components.size() && i<iteration_limit;++i,components=next(components,initial,limit,primes)) {
        auto fraction = quotient(components);

        if(is_permuted_pair(fraction.p(),fraction.q())) {
            if(!util::test_mode()) {
                fmt::print("[{}] {}x{} -> {} ({})\n",i,
                                                *components[0],
                                                *components[1],
                                                 fraction,
                                                 static_cast<double>(fraction));
            }
            return std::make_tuple(true,fraction);
        };
    }

    return std::make_tuple(false,quotient(Components{}));
}

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);

    if(argc != 2) {
        fmt::print("Usage: {} <n upper bound>\n", argv[0]);
        return 1;
    }

    const uint32_t limit = std::stoi(argv[1]);
    const auto &primes = PrimeNumbers(limit);

    auto result = search(limit, primes);

    if(std::get<0>(result)) {
        fmt::print("{}\n", std::get<1>(result).p());
    } else {
        fmt::print("Failed\n");
    }

    return 0;
}
