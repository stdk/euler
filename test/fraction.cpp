#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cstdint>
#include <util.h>
#include <fraction.h>

typedef Fraction<uint32_t> ufraction;
typedef Fraction<int32_t> fraction;

TEST_CASE( "assignment", "[assignment]" ) {
    REQUIRE(to_string(fraction(ufraction{1,2})) == "1/2");
    REQUIRE(to_string(ufraction(fraction{1,2})) == "1/2");
}


TEST_CASE( "simplify" , "[simplify]" ) {
    {
        ufraction f{25,5};
        auto x = f.simplify();
        REQUIRE(to_string(x) == "5/1");
    }

    {
        ufraction f{13,7};
        auto x = f.simplify();
        REQUIRE(to_string(x) == "13/7");
    }

    {
        ufraction f{0,0};
        auto x = f.simplify();
        REQUIRE(to_string(x) == "0/0");
    }

    {
        ufraction f{5,0};
        auto x = f.simplify();
        REQUIRE(to_string(x) == "1/0");
    }

    {
        ufraction f{0,7};
        auto x = f.simplify();
        REQUIRE(to_string(x) == "0/1");
    }
}
