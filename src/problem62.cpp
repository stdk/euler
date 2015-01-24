#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cstdint>
#include <util.h>

uint64_t search(const size_t limit, const size_t desired_count) {
	std::unordered_map<uint64_t,std::vector<uint64_t>> cubes_table;

	for(uint64_t i=2;i<limit;i++) {
		uint64_t cube = i*i*i;
		auto digits = digit_deconstruct(cube);
		std::sort(digits.rbegin(),digits.rend());
		uint64_t digit_id = digit_reconstruct(digits);

		auto &cubes = cubes_table[digit_id];
		cubes.push_back(cube);
		if(cubes.size() >= desired_count) {
			for(auto x: cubes) {
				std::cout << x << " ";
			}
			std::cout << std::endl;
			return cubes[0];
		}
	}
	return 0;
}

int main(int argc, char **argv) {
	std::ios_base::sync_with_stdio(false);
	const size_t limit = 10000;
	const size_t desired_count = 5;

	Measure measure;

	uint64_t min_cube = search(limit,desired_count);

	auto passed = measure.passed();
	std::cout << "Search took " << passed << " ms" << std::endl;
	std::cout << "Minimal cube with given property: " << min_cube << std::endl;

	return 0;
}
