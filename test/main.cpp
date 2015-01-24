#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <util.h>

TEST_CASE( "perfect_square_root", "[perfect_square_root]" ) {
	const size_t limit = 100;

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
	const size_t limit = 100000;

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
