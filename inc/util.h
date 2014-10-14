#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <sstream>
#include <chrono>
#include <functional>
#include <memory>
#include <cstdio>

using UniqueIostreamPtr = std::unique_ptr<std::istream,std::function<void(std::istream*)>>;

UniqueIostreamPtr get_input_stream(int argc, char **argv) {
    UniqueIostreamPtr in(&std::cin, [](std::istream*){});
    if(argc > 1) in = UniqueIostreamPtr(new std::ifstream(argv[1]),[](std::istream* p) {
        delete p;
    });
    return in;
}

using UniqueFILEPtr = std::unique_ptr<std::FILE, std::function<void(std::FILE*)>>;

UniqueFILEPtr get_input_file(int argc, char **argv) {
    UniqueFILEPtr f(stdin, [](std::FILE*) {});

    if(argc > 1) f = UniqueFILEPtr(fopen(argv[1],"r"),[](std::FILE *f) {
        fclose(f);
    });

    return f;
}

std::chrono::milliseconds measure(std::function<void()> callback) {
    auto start = std::chrono::high_resolution_clock::now();
    callback();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
}

template<class InputIterator>
std::string join(const std::string &delim, InputIterator begin, InputIterator end) {
	std::ostringstream out;
	if(begin != end) out << *begin;
	while(++begin!=end) out << delim << *begin;
	return out.str();
}

template<class T, size_t N>
char *itoa(T num, char (&buffer)[N], size_t radix=10) {
    char *out = buffer + N;
    bool minus = std::signbit(num);
    num = std::abs(num);
    *--out = 0;
    if(num) {
        for(; out != buffer && num; num/=radix) {
            *--out = "0123456789ABCDEFGHIJKLMNOPQRSTYVWXYZabcdefghijklmnopqrstyvwxyz"[num % radix];
        }
    } else {
        *--out='0';
    }
    if(out != buffer && minus) *--out='-';
    return out;
}

#endif
