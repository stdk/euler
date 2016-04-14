#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <util.h>

void process(std::istream &stream, size_t *numbers, size_t count) {
    size_t new_count = count + 1;
    std::unique_ptr<size_t[]> new_numbers(new size_t[new_count]);

    for(size_t i=0;i<new_count;i++) {
        if(!(stream >> new_numbers[i])) return;

        if(!util::test_mode()) {
            std::cout.width(3);
            std::cout.fill('0');
            std::cout << new_numbers[i] << " ";
        }
    }
    if(!util::test_mode()) std::cout << std::endl;
    
    process(stream, new_numbers.get(), new_count);

    if(!util::test_mode()) {
        for(size_t i=0;i<new_count;i++) {
            std::cout.width(3);
            std::cout.fill('0');
            std::cout << new_numbers[i] << " ";
        }
        std::cout << std::endl;
    }

    for(size_t i=0;i<count;i++) {
        numbers[i] += std::max(new_numbers[i], new_numbers[i+1]);
    }
}

size_t get_max_sum(std::istream &stream) {
    size_t result;
    stream >> result;
    if(!util::test_mode()) {
        std::cout << result << std::endl;
    }
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
