#include <iostream>
#include <cstdint>
#include <array>
#include <util.h>

static std::array<uint32_t,10> digit_factorials = {
    factorial<0>::value,
    factorial<1>::value,
    factorial<2>::value,
    factorial<3>::value,
    factorial<4>::value,
    factorial<5>::value,
    factorial<6>::value,
    factorial<7>::value,
    factorial<8>::value,
    factorial<9>::value,
};

uint32_t digit_factorials_sum(uint32_t n) {
    uint32_t r = 0;
    for(;n;n/=10) {
        r += digit_factorials[n%10];
    }
    return r;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    const uint32_t limit = digit_factorials[9];
    uint32_t sum = 0;

    for(uint32_t i=3;i<limit;i++) {
        if(digit_factorials_sum(i) == i) {
            sum += i;
        }
    }

    std::cout << sum << std::endl;

    return 0;
}
