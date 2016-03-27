#include <iostream>
#include <numeric>
#include <functional>
#include <gmpxx.h>
#include <util.h>

int main() {
	mpz_class number;

	mpz_ui_pow_ui(number.get_mpz_t(), 2, 1000);

	auto str = number.get_str();
	auto sum = std::accumulate(str.begin(), str.end(), (size_t)0, [](size_t a, size_t b) {
		return a + b - 0x30;
	});

	if(!util::test_mode()) {
		std::cout << str << "(" << str.size() << "): ";
	}
	std::cout << sum << std::endl;

	return 0;
}
