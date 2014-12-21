#include <iostream>
#include <fstream>
#include <string>
#include <numeric>
#include <algorithm>
#include "custom_locale.h"

inline size_t tr(size_t i) {
	return i*(i+1)/2;
}

std::vector<size_t> generate_triangle_numbers(size_t limit) {
	std::vector<size_t> numbers;
	for(size_t i=1,n=tr(i);n<limit;i++,n=tr(i)) numbers.push_back(n);
	return numbers;
}

size_t count_triangle_words(std::istream &in,const std::vector<size_t> &triangle_numbers) {
	size_t count = 0;
	std::string word;
	while(in >> word) {
		size_t value = std::accumulate(word.begin(),word.end(),(size_t)0,[](size_t v, char c) {
			return v += c - 'A' + 1;
		});
		if(std::binary_search(triangle_numbers.begin(),triangle_numbers.end(),value)) count++;
		//std::cout << word << " = " << value << std::endl;
	}
	return count;
}

int main(int argc, char **argv) {
	std::ios_base::sync_with_stdio(false);

	if(argc < 2) {
		std::cout << "Please specify input filename." << std::endl;
		return 1;
	}

	auto triangle_numbers = generate_triangle_numbers(200);

	std::locale::global(std::locale(std::locale(), new csv_locale()));
	std::fstream in(argv[1]);

	std::cout << "Triangle words: " << count_triangle_words(in,triangle_numbers) << std::endl;

	return 0;
}
