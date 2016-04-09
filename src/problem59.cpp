#include <iostream>
#include <iterator>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>
#include <custom_locale.h>
#include <util.h>

const size_t key_length = 3;

struct entry {
	uint8_t byte;
	size_t count;

	bool operator<(const entry &other) const {
		return count < other.count;
	}
};

using Frequency = std::vector<std::vector<entry>>;

std::vector<uint8_t> read(const std::string &filename) {
	std::vector<uint8_t> data;

	std::ifstream in(filename);
	if(!in) {
		std::cerr << "Cannot open " << filename << std::endl;
		return data;
	}

	std::istream_iterator<uint16_t> begin(in),end;
	data.assign(begin,end);

	return data;
}

Frequency count_frequency(const std::vector<uint8_t> &data) {
	Frequency frequency(key_length,std::vector<entry>(0xFF,{0,0}));

	for(auto &v: frequency) {
		for(auto i=v.begin();i!=v.end();++i) {
			i->byte = i - v.begin();
		}
	}

	auto b = data.begin();
	for(auto i=b;i!=data.end();++i) {
		//if((i-b) && (i-b)%120 == 0) std::cout << std::endl;
		//std::cout << std::setw(2) << std::setfill('0') << std::hex << (unsigned)*i;
		frequency[(i-b)%key_length][*i].count++;
	}

	for(auto &v: frequency) {
		std::sort(v.rbegin(),v.rend());
	}
	return frequency;
}

std::vector<uint8_t> get_key(const Frequency &frequency) {
	std::vector<uint8_t> key(3);
	for(auto v=frequency.begin();v!=frequency.end();++v) {
		key[v-frequency.begin()] = ' '^(*v)[0].byte;
	}
	return key;
}

int main(int argc, char **argv) {
	std::ios_base::sync_with_stdio(false);
	std::locale::global(std::locale(std::locale(), new csv_locale()));

	if(argc < 2) {
		std::cerr << "Please specify input filename." << std::endl;
		return 1;
	}

	Measure measure;
	auto data = read(argv[1]);
	auto passed = measure.passed();
	if(!util::test_mode()) {
		std::cout << "Reading took " << passed << " ms" << std::endl;
		std::cout << "Data length: " << data.size() << std::endl;
	}

	auto frequency = count_frequency(data);
	auto key = get_key(frequency);

	size_t sum = 0;
	for(auto i=data.begin();i!=data.end();i++) {
		sum += *i^key[(i-data.begin())%key_length];
	}

	std::cout << std::dec << sum << std::endl;

	return 0;
}
