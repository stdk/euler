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

void test_problem(const std::string &command, const std::string &expected) {
	REQUIRE(putenv("TEST_MODE=1")==0);
	REQUIRE(get_output(command) == expected);
	REQUIRE(putenv("TEST_MODE=")==0);
}


TEST_CASE("problem4", "[problem4]") {
	test_problem("problem4", "906609\n");
}

TEST_CASE("problem11", "[problem11]") {
	test_problem("problem11", "70600674\n");
}

TEST_CASE("problem12", "[problem12]") {
	test_problem("problem12", "76576500\n");
}

TEST_CASE("problem14", "[problem14]") {
	test_problem("problem14", "837799\n");
}

TEST_CASE("problem15", "[problem15]") {
	test_problem("problem15", "137846528820\n");
}

TEST_CASE("problem16", "[problem16]") {
	test_problem("problem16", "1366\n");
}

TEST_CASE("problem18", "[problem18]") {
	test_problem("problem18 input/input18.txt", "1074\n");
}

TEST_CASE("problem20", "[problem20]") {
	test_problem("problem20", "648\n");
}

TEST_CASE("problem22", "[problem22]") {
	test_problem("problem22 input/input22.txt", "871198282\n");
}

TEST_CASE("problem23", "[problem23]") {
	test_problem("problem23", "4179871\n");
}

TEST_CASE("problem24", "[problem24]") {
	test_problem("problem24", "2783915460\n");
}

TEST_CASE("problem25", "[problem25]") {
	test_problem("problem25", "4782\n");
}

TEST_CASE("problem26", "[problem26]") {
	test_problem("problem26", "983\n");
}

TEST_CASE("problem64", "[problem64]") {
	test_problem("problem64", "1322\n");
}

TEST_CASE("problem65", "[problem65]") {
	test_problem("problem65", "272\n");
}

TEST_CASE("problem66", "[problem66]") {
	test_problem("problem66 1000", "661\n");
}

TEST_CASE("problem67", "[problem67]") {
	test_problem("problem18 input/input67.txt", "7273\n");
}

TEST_CASE("problem68", "[problem68]") {
	test_problem("problem68", "6531031914842725\n");
}
