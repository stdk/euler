#include <iostream>
#include <cstdint>

uint64_t pow_mod(uint64_t n, size_t p, uint64_t mod) {
	uint64_t r = 1;
	while(p--) {
		r = r*n % mod;
	}
	return r;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	const uint64_t mod = 10000000000;

	uint64_t s = 0;
	for(uint32_t i=1;i<=1000;i++) {
		s = (s + pow_mod(i,i,mod)) % mod;
	}

	std::cout << s << std::endl;

	return 0;
}
