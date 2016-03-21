#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <util.h>

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
