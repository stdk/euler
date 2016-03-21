#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <sstream>
#include <cstdio>
#include <cstdlib>

std::string get_output(const std::string &command) {
	FILE *stream = popen(command.c_str(),"r");
	REQUIRE(stream != 0);

	std::ostringstream os;

	char data[512];

	while (fgets(data, sizeof(data), stream) != NULL) {
		os << data;
	}

	REQUIRE(fclose(stream) != -1);

	return os.str();
}

TEST_CASE( "problems", "[problems]" ) {
	REQUIRE(putenv("TEST_MODE=1")==0);

	REQUIRE(get_output("problem11") == "70600674\n");

	REQUIRE(putenv("TEST_MODE=")==0);
}
