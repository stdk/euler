#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <algorithm>
#include <functional>
#include <util.h>
#include <primes.h>

TEST_CASE( "digit_count", "[digit_count]" ) {
	REQUIRE(digit_count(0) == 1);
	REQUIRE(digit_count(1) == 1);
	REQUIRE(digit_count(10) == 2);
	REQUIRE(digit_count(123456790) == 9);
	REQUIRE(digit_count(01234567,8) == 7);
	REQUIRE(digit_count(0b1010101010,2) == 10);
	REQUIRE(digit_count(0xABCDEF,16) == 6);
}

TEST_CASE( "digit_deconstruct", "[digit_deconstruct]") {
	REQUIRE(digit_deconstruct(0) == std::vector<uint32_t>({0}));
	REQUIRE(digit_deconstruct(01234567,8) == std::vector<uint32_t>({1,2,3,4,5,6,7}));
	REQUIRE(digit_deconstruct(0b1010101010,2) == std::vector<uint32_t>({1,0,1,0,1,0,1,0,1,0}));
	REQUIRE(digit_deconstruct(1234567890) == std::vector<uint32_t>({1,2,3,4,5,6,7,8,9,0}));
	REQUIRE(digit_deconstruct(0xABCDEF,16) == std::vector<uint32_t>({0xA,0xB,0xC,0xD,0xE,0xF}));
	REQUIRE(digit_deconstruct(101782150309ul) == std::vector<uint32_t>({1,0,1,7,8,2,1,5,0,3,0,9}));

}

TEST_CASE( "digit_reconstruct", "[digit_reconstruct]") {
	REQUIRE(digit_reconstruct(std::vector<uint32_t>({0})) == 0);
	REQUIRE(digit_reconstruct(std::vector<uint32_t>({1,2,3,4,5,6,7}),8) == 01234567);
	REQUIRE(digit_reconstruct(std::vector<uint32_t>({1,0,1,0,1,0,1,0,1,0}),2) == 0b1010101010);
	REQUIRE(digit_reconstruct(std::vector<uint32_t>({1,2,3,4,5,6,7,8,9,0})) == 1234567890);
	REQUIRE(digit_reconstruct(std::vector<uint32_t>({0xA,0xB,0xC,0xD,0xE,0xF}),16) == 0xABCDEF);
}

TEST_CASE( "perfect_square_root", "[perfect_square_root]" ) {
	const size_t limit = 10000;

	std::vector<bool> n(limit,false);
	n[0] = true;
	for(int64_t i=1;i<limit;i++) {
		int64_t square = i*i;
		if((square - 1) < n.size()) {
			n[square - 1] = true;
		}
		REQUIRE(perfect_square_root(square) == i);

		if(!n[i-1]) {
			REQUIRE(perfect_square_root(i) == -1);
		}
	}
}

TEST_CASE( "perfect_cubic_root", "[perfect_cubic_root]" ) {
	const size_t limit = 10000;

	std::vector<bool> n(limit,false);
	n[0] = true;
	for(int64_t i=1;i<limit;i++) {
		int64_t cube = i*i*i;
		if((cube - 1) < n.size()) {
			n[cube - 1] = true;
		}
		REQUIRE(perfect_cubic_root(cube) == i);

		if(!n[i-1]) {
			REQUIRE(perfect_cubic_root(i) == -1);
		}
	}
}

TEST_CASE( "gcd", "[gcd]" ) {
	const size_t limit = 1000;
	const auto &primes = PrimeNumbers(limit);

	auto accumulator = [](size_t product, const Factor &factor) {
	   for(size_t i=0;i<factor.count;++i) {
		   product *= factor.prime;
	   }
	   return product;
	};

	for(size_t a=0;a<limit;++a) {
		for(size_t b=0;b<limit;++b) {
			size_t reference_gcd;
			if(a == 0 || b == 0) {
				if(a == b) {
					reference_gcd = 1;
				} else {
					reference_gcd = std::max(a,b);
				}
			} else {
				auto factors_a = factorize(a,primes);
				auto factors_b = factorize(b,primes);

				auto common = common_factors(factors_a, factors_b);
				reference_gcd = std::accumulate(common.begin(),
				  							    common.end(),
												(size_t)1,
												accumulator);
			}

			INFO(to_string(a) + "," + to_string(b));
			REQUIRE(gcd(a,b) == reference_gcd);
		}
	}
}
