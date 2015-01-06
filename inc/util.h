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
#include <cstdint>

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

class Measure {
	std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();
public:
	void reset() {
		begin = std::chrono::high_resolution_clock::now();
	}

	size_t passed() const {
		auto now = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::milliseconds>(now - begin).count();
	}
};

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

int64_t perfect_square_root(int64_t x) {
	if(x < 0) return -1;
	if(x < 2) return x;
	int64_t a = x;
	int64_t b = x/2;
	while(a > b) {
		a = b;
		b = (a + x/b)/2;
	}
	if(b*b == x) {
		return b;
	}
	return -1;
}

//find next k-combination
bool next_combination(uint32_t &x, uint32_t mask) {
	uint32_t u = x & -x; // extract rightmost bit 1
	uint32_t v = u + x; // set last non-trailing bit 0 and clear to the right
	if((v&mask) == 0) return false; // overflow i v or x==0
	x = v + (((v^x)/u)>>2);
	return true;
}

template<size_t x,size_t a, size_t b>
struct power_impl : power_impl<x*a,a,b-1> {};

template<size_t x,size_t a>
struct power_impl<x,a,0> : std::integral_constant<size_t,1> {};

template<size_t x,size_t a>
struct power_impl<x,a,1> : std::integral_constant<size_t,x> {};

template<size_t a,size_t b>
using power = power_impl<a,a,b>;

#endif
