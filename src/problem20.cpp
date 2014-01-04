#include <iostream>
#include <numeric>
#include <functional>
#include <gmpxx.h>

int main() {
	mpz_class number;

	mpz_fac_ui(number.get_mpz_t(), 100);

	auto str = number.get_str();
	auto sum = std::accumulate(str.begin(), str.end(), (size_t)0, [](size_t a, size_t b) {
		return a + b - 0x30;
	});

	std::cout << str << "(" << str.size() << "): " << sum << std::endl;
	return 0;
}
