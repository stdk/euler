#include <iostream>
#include <gmpxx.h>
#include <util.h>

int main(int argc, char **argv) {
	std::ios_base::sync_with_stdio(false);
	const size_t limit = 100;

	Measure measure;

	mpz_class number;

	uint64_t max_sum = 0;
	for(size_t a = 1;a<limit;a++) {
		for(size_t b = 1;b<limit;b++) {
			mpz_ui_pow_ui(number.get_mpz_t(), a, b);
			auto str = number.get_str();
			auto sum = std::accumulate(str.begin(), str.end(), (uint64_t)0, [](uint64_t s, size_t x) {
				return s + x - 0x30;
			});
			if(sum > max_sum) {
				max_sum = sum;
			}
		}
	}

	auto passed = measure.passed();
	std::cout << "Search took " << passed << " ms" << std::endl;
	std::cout << "Max sum: " << max_sum << std::endl;

	return 0;
}
