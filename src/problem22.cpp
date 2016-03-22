#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <util.h>
#include "custom_locale.h"

size_t word_value(const std::string &word, size_t idx) {
    return idx*std::accumulate(word.begin(),word.end(), (size_t)0, [](size_t total, char c) -> size_t {
        return total + c - 'A' + 1;
    });
}

std::vector<std::string> read(std::istream &is) {
    std::vector<std::string> words;

    std::istream_iterator<std::string> begin(is),end;
    words.assign(begin,end);

    std::stable_sort(words.begin(), words.end());

    return words;
}

size_t get_value(const std::vector<std::string> &words) {
    size_t total = 0;

    for(size_t i=0;i<words.size();i++) {
        size_t value = word_value(words[i],i+1);
        //std::cout << words[i] << " " << i+1 << " " << value << std::endl;
        total += value;
    }

    return total;
}

int main(int argc, char **argv) {
	std::ios_base::sync_with_stdio(false);

    if(argc < 2) {
        std::cout << "Please specify input filename." << std::endl;
        return 1;
    }

    std::locale::global(std::locale(std::locale(), new csv_locale()));

    std::fstream input(argv[1]);
    if(!util::test_mode) {
    	std::cout << "Value: ";
    }
    std::cout << get_value(read(input)) << std::endl;
}
