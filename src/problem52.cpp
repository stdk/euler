#include <iostream>
#include <util.h>
#include <cstdint>

int32_t digit_mask(uint32_t number) {
	int32_t mask = 0;

	while(number) {
		uint32_t digit_bit = 1 << (number%10);
		if(mask & digit_bit) return -1;
		mask |= digit_bit;
		number /= 10;
	}

	return mask;
}

bool check_number(uint32_t number) {
	int32_t mask = digit_mask(number);
	if(-1 == mask) return false;

	for(uint32_t i=2;i<=6;i++) {
		if(digit_mask(number*i) != mask) return false;
	}

	return true;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	Measure measure;
	for(uint32_t i=power<10,5>::value;i<power<10,7>::value;i++) {
		if(check_number(i)) {
			std::cout << i << std::endl;
			break;
		}
	}
	auto passed = measure.passed();

	if(!util::test_mode()) {
		std::cout << "Search took " << passed << " ms" << std::endl;
	}
	return 0;
}
