#include <iostream>
#include <cstdint>
#include <util.h>

uint32_t f(uint32_t x, uint32_t y, uint32_t z) {
	return z*(10*y + x) - y*(10*x+z);
}

int main() {
	uint32_t p = 1;
	uint32_t q = 1;

	for(uint32_t x=1;x<10;++x) {
		for(uint32_t y=1;y<10;++y) {
			for(uint32_t z=1;z<10;++z) {
				if((x!=y || y!=z) && f(x,y,z) == 0) {
					p *= y;
					q *= z;
				}
			}
		}
	}

	std::cout << q / gcd(p,q) << std::endl;

	return 0;
}
