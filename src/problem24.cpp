#include <iostream>
#include <array>
#include <algorithm>
#include <numeric>

template<class BidirIt>
bool next_permutation(BidirIt begin, BidirIt end) {
	if(begin == end) return false; // no elements
	BidirIt pivot = end;
	if(begin == --pivot) return false; //single element

	while(*pivot < *(pivot-1)) {
		if(--pivot == begin) { // last permutation already
			std::reverse(begin,end);
			return false;
		}
	}
	--pivot;

	BidirIt candidate = end;
	while(*--candidate < *pivot);
	std::iter_swap(pivot,candidate);

	std::reverse(pivot+1,end);

	return true;
}

template<size_t N>
struct fact : std::integral_constant<size_t, N*fact<N-1>::value> {};

template<>
struct fact<1> : std::integral_constant<size_t, 1> {};

int main(int argc, char **argv) {
	const size_t len = 10;
	std::array<size_t,len> a;
	std::iota(a.begin(),a.end(),0);
	std::array<size_t,len> b = a;

	for(size_t i=0;i<1000000-1;i++) {
		next_permutation(a.begin(), a.end());
		std::next_permutation(b.begin(), b.end());
	}

	std::cout << "next_permutation: ";
	for(auto e: a) std::cout << e;
	std::cout << std::endl;

	std::cout << "std::next_permutation: ";
	for(auto e: b) std::cout << e;
		std::cout << std::endl;

	return 0;
}
