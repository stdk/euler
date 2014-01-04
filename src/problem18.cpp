#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <alloca.h>

void process(std::istream &stream, size_t *numbers, size_t count) {
	size_t new_count = count + 1;
        size_t *new_numbers = (size_t*)alloca(sizeof(size_t) * new_count);

	for(size_t i=0;i<new_count;i++) {
		stream >> new_numbers[i];
		if(!stream) return;

		std::cout.width(3);
		std::cout.fill('0');
		std::cout << new_numbers[i] << " ";
	}
	std::cout << std::endl;
	
	process(stream, new_numbers, new_count);

	for(size_t i=0;i<new_count;i++) {
		std::cout.width(3);
		std::cout.fill('0');
		std::cout << new_numbers[i] << " ";
	}
	std::cout << std::endl;

	for(size_t i=0;i<count;i++) {
		numbers[i] += std::max(new_numbers[i], new_numbers[i+1]);
	}
}

size_t get_max_sum(std::istream &stream) {
	size_t result;
	stream >> result;
	std::cout << result << std::endl;
	process(stream, &result, 1);	
	return result;
}

int main(int argc, char **argv) {
	if(argc < 2) {
		std::cout << "Please specify input filename." << std::endl;
		return 1;
	}

	std::ifstream file(argv[1]);
	if(!file) {
		std::cout << "Cannot open file: " << argv[1] << std::endl;
		return 2;
	}

	std::cout << get_max_sum(file) << std::endl;

	return 0;
}
