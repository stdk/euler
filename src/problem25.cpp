#include <iostream>
#include <numeric>
#include <cmath>
#include <gmpxx.h>
#include <util.h>

mpf_class fibonacci_number(mpf_class sqrt5, mpf_class f_a, mpf_class f_b, size_t i) {
    mpf_pow_ui(f_a.get_mpf_t(),f_a.get_mpf_t(),i);
    mpf_pow_ui(f_b.get_mpf_t(),f_b.get_mpf_t(),i);

    return ceil(f_b/sqrt5 - f_a/sqrt5);
}

long int get_exp(const mpf_class &n) {
    return gmp_snprintf(0,0,"%.0Ff",n.get_mpf_t());
}

int main() {
    mpf_class sqrt5 = sqrt(5_mpf);
    mpf_class f_a = (1_mpf - sqrt5)/2_mpf;
    mpf_class f_b = (1_mpf + sqrt5)/2_mpf;

    auto fib = [&](size_t i) {
        return fibonacci_number(sqrt5,f_a,f_b,i);
    };

    size_t begin = 100;
    size_t end = 10000;

    while(begin <= end) {
        size_t mid = (end - begin)/2 + begin;

        auto f = fib(mid);
        size_t e = get_exp(f);

        if(!util::test_mode()) {
            std::cout << begin << " [" << mid << "] " << end << " -> " << f << " | " << e << std::endl;
        }

        if(e >= 1000) {
            end = mid - 1;
        } else {
            begin = mid + 1;
        }
    }

    std::cout << begin << std::endl;

    return 0;
}
