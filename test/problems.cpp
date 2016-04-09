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

TEST_CASE("problem19", "[problem19]") {
	test_problem("problem19", "171\n");
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

TEST_CASE("problem27", "[problem27]") {
	test_problem("problem27", "-59231\n");
}

TEST_CASE("problem29", "[problem29]") {
	test_problem("problem29 100", "9183\n");
}

TEST_CASE("problem31", "[problem29]") {
	test_problem("problem31", "73682\n");
}

TEST_CASE("problem32", "[problem32]") {
	test_problem("problem32", "45228\n");
}

TEST_CASE("problem33", "[problem33]") {
	test_problem("problem33", "100\n");
}

TEST_CASE("problem34", "[problem34]") {
	test_problem("problem34", "40730\n");
}

TEST_CASE("problem35", "[problem35]") {
	test_problem("problem35", "55\n");
}

TEST_CASE("problem36", "[problem36]") {
	test_problem("problem36", "872187\n");
}

TEST_CASE("problem37", "[problem37]") {
	test_problem("problem37", "748317\n");
}

TEST_CASE("problem40", "[problem40]") {
	test_problem("problem40", "210\n");
}

TEST_CASE("problem41", "[problem41]") {
	test_problem("problem41", "7652413\n");
}

TEST_CASE("problem42", "[problem42]") {
	test_problem("problem42 input/input42.txt", "162\n");
}

TEST_CASE("problem43", "[problem43]") {
	test_problem("problem43", "16695334890\n");
}

TEST_CASE("problem44", "[problem44]") {
	test_problem("problem44", "5482660\n");
}

TEST_CASE("problem45", "[problem45]") {
	test_problem("problem45", "1533776805\n");
}

TEST_CASE("problem46", "[problem46]") {
	test_problem("problem46", "5777\n");
}

TEST_CASE("problem47", "[problem47]") {
	test_problem("problem47", "134043\n");
}

TEST_CASE("problem48", "[problem48]") {
	test_problem("problem48", "9110846700\n");
}

TEST_CASE("problem49", "[problem49]") {
	test_problem("problem49", "296962999629\n");
}

TEST_CASE("problem50", "[problem50]") {
	test_problem("problem50", "997651\n");
}

TEST_CASE("problem51", "[problem51]") {
	test_problem("problem51", "121313\n");
}

TEST_CASE("problem52", "[problem52]") {
	test_problem("problem52", "142857\n");
}

TEST_CASE("problem53", "[problem53]") {
	test_problem("problem53", "4075\n");
}

TEST_CASE("problem54 ", "[problem54]") {
	test_problem("problem54 input/input54.txt", "376\n");
}

TEST_CASE("problem55", "[problem55]") {
	test_problem("problem55", "249\n");
}

TEST_CASE("problem56", "[problem56]") {
	test_problem("problem56", "972\n");
}

TEST_CASE("problem57", "[problem57]") {
	test_problem("problem57", "153\n");
}

TEST_CASE("problem58", "[problem58]") {
	test_problem("problem58", "26241\n");
}

TEST_CASE("problem59", "[problem59]") {
	test_problem("problem59 input/input59.txt", "107359\n");
}

TEST_CASE("problem60", "[problem60]") {
	test_problem("problem60", "26033\n");
}

TEST_CASE("problem61", "[problem61]") {
	test_problem("problem61", "28684\n");
}

TEST_CASE("problem62", "[problem62]") {
	test_problem("problem62", "127035954683\n");
}

TEST_CASE("problem63", "[problem63]") {
	test_problem("problem63", "49\n");
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

TEST_CASE("problem69", "[problem69]") {
	test_problem("problem69 1000000", "510510\n");
}
