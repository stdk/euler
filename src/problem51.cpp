#include <iostream>
#include <bitset>
#include <vector>
#include <algorithm>
#include <primes.h>
#include <util.h>
#include <type_traits>
#include <cstdint>

template<size_t x,size_t a, size_t b>
struct power_impl : power_impl<x*a,a,b-1> {};

template<size_t x,size_t a>
struct power_impl<x,a,0> : std::integral_constant<size_t,1> {};

template<size_t x,size_t a>
struct power_impl<x,a,1> : std::integral_constant<size_t,x> {};

template<size_t a,size_t b>
struct power : power_impl<a,a,b> {};

template<size_t base>
prime_t fill_by_mask(uint32_t pattern, uint32_t mask, uint32_t filler) {
	size_t order = 1;
	prime_t result = 0;

	while(pattern || mask) {
		if(mask & 1) {
			result += filler%base*order;
			filler /= base;
		} else {
			result += pattern%base*order;
		}
		order *= base;
		mask >>= 1;
		pattern /= base;
	}

	return result;
}

std::vector<uint8_t> same_digit_masks(prime_t number) {
	std::vector<uint8_t> masks;

	uint8_t digit_counter[10] = {0};
	prime_t n = number;
	while(n) {
		digit_counter[n%10]++;
		n /= 10;
	}

	for(size_t i=0;i<10;i++) {
		if(digit_counter[i]>1) {
			uint8_t mask = 0;
			for(prime_t n=number,k=0;n;n/=10,k++) {
				if(n%10==i) mask |= (1 << k);
			}
			masks.push_back(mask);
		}
	}
	return masks;
}

uint32_t repeat_digit(uint32_t digit,size_t count) {
	uint32_t result = 0;
	while(count--) {
		result = result*10 + digit;
	}
	return result;
}

template<class PrimeContainer>
std::vector<prime_t> count_group_size(prime_t pattern,uint32_t mask,size_t mask_len,const PrimeContainer &primes) {
	std::vector<prime_t> group;

	for(uint32_t i=0;i<10;i++) {
		prime_t candidate = fill_by_mask<10>(pattern,mask,repeat_digit(i,mask_len));
		if(candidate >= pattern && primes[candidate]) {
			group.push_back(candidate);
		}
	}

	return group;
}

template<class Iterator, class PrimeContainer>
prime_t search(Iterator begin, Iterator end, const PrimeContainer &primes) {
	for(auto i=begin;i!=end;++i) {
		for(auto mask: same_digit_masks(*i)) {
			const size_t mask_len = __builtin_popcount(mask);
			const size_t mask_mask = (1 << mask_len) - 1;
			for(size_t len = mask_len;len>1;len--) {
				for(uint32_t bits = (1 << len) - 1,ok=1;ok;ok=next_combination(bits,mask_mask)) {
					uint32_t m = fill_by_mask<2>(0,mask,bits);
					auto group = count_group_size(*i,m,len,primes);
					if(group.size() > 7) {
						for(auto e: group) {
							std::cout << e << " ";
						}
						std::cout << std::endl;
						return group[0];
					}
				}
			}
		}
	}
	return 0;
}

int main(int argc, char **argv) {
	std::ios_base::sync_with_stdio(false);

	const size_t digit_count = 6;
	const prime_t limit = power<10,digit_count>::value;

	Measure measure;
	const auto &primes = PrimeNumbers(limit);
	auto passed = measure.passed();
	std::cout << "Prime generation took: " << passed << " ms" << std::endl;

	auto begin = std::lower_bound(primes.begin(),primes.end(),power<10,digit_count-1>::value);
	auto end = std::lower_bound(primes.begin(),primes.end(),limit);

	measure.reset();
	uint32_t prime = search(begin,end,primes);
	passed = measure.passed();
	std::cout << "Search for " << prime << " took: " << passed << " ms" << std::endl;

	return 0;
}
