#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <algorithm>
#include <vector>
#include <cstdint>
#include <cppformat/format.h>

TEST_CASE( "std::rotate", "[std::rotate]" ) {
	std::vector<int> v  = {1,2,3,4,5,6,7};
	std::vector<int> v2 = {6,7,1,2,3,4,5};

	std::rotate(v.begin(),v.begin()+5,v.end());

	REQUIRE(v == v2);
}
