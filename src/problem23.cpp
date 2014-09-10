#include <iostream>
#include <numeric>
#include <tuple>
#include <primes.h>

std::vector<size_t> get_all_divisors(const CompactFactors &factors) {
    std::vector<size_t> divisors = {1};

    for(auto i = factors.cbegin(); i<factors.cend();++i) {
        size_t divisor = 1;
        for(size_t j = 0;j<std::get<1>(*i);j++) {
            divisor *= std::get<0>(*i);
            divisors.push_back(divisor);
            for(auto k=i+1;k!=factors.cend();++k) {
                divisors.push_back(divisor*std::get<0>);
            }
        }
    }

    return divisors;
}

int main() {
    auto primes = generate_primes(1000000);

    for(size_t i=1;i<100;i++) {
        auto divisors = factorize_compact(i,primes);
        size_t sum = std::accumulate(divisors.begin(), divisors.end(), (size_t)0, [](size_t s, CompactFactor &f) {
            return s + std::get<0>(f);
        });
        if(sum == i + 1) {
            std::cout << i << " " << "is a perfect number" << std::endl;
        }
    }

    std::cout << "Hello world!" << std::endl;
    return 0;
}