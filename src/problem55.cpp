#include <iostream>
#include <util.h>

template<typename T>
bool is_palindrome(T number) {
    //log(2)/log(10) is equal to about 0.3 so we can estimate length of the string required to contain our input
    char buffer[sizeof(number)*8*3/10 + 1 + 1];// + tailing zero byte + extra byte for
    char *last = buffer + sizeof(buffer) - 2;
    char *first = itoa(number,buffer);
    while(first < last) {
        if(*first++ != *last--) return false;
    }

    return true;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    const uint32_t limit = 10000;

    //89 takes an unusually large 24 iterations
    //(the most of any number under 10,000 that is known to resolve into a palindrome)
    //to reach the palindrome 8,813,200,023,188.
    const size_t max_attempts = 25;

    Measure measure;

    size_t count = limit - 1;
    for(uint32_t i=1;i<limit;i++) {
        uint64_t n = i;
        for(size_t k=0;k<max_attempts;k++) {
            n = n + reverse_digits(n);
            if(is_palindrome(n)) {
                count--;
                break;
            }
        }
    }

    auto passed = measure.passed();

    if(!util::test_mode()) {
        std::cout << "Search took " << passed << " ms" << std::endl;
        std::cout << "There are " << count << " possible Lychrel numbers below " << limit << std::endl;
    } else {
        std::cout << count << std::endl;
    }

    return 0;
}
