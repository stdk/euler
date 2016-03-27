#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>
#include <functional>
#include <type_traits>
#include <memory>
#include <cstdio>
#include <cstdint>
#include <cstdlib>

namespace util {
	const char *test_mode_str = std::getenv("TEST_MODE");
	const bool test_mode_state = util::test_mode_str ? std::string(util::test_mode_str) == "1" : false;

	inline bool test_mode() {
		return test_mode_state;
	}
}

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


template<class T, size_t N, class Enable=void>
struct itoa_impl {
	static_assert(std::is_integral<T>::value == true,"This function accepts only integers");
};

template<class T, size_t N>
struct itoa_impl<T,N,typename std::enable_if<std::is_integral<T>::value && std::is_signed<T>::value>::type> {
	static char *itoa(T num, char (&buffer)[N], size_t radix) {
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
};

template<class T, size_t N>
struct itoa_impl<T,N,typename std::enable_if<std::is_integral<T>::value && std::is_unsigned<T>::value>::type> {
	static char *itoa(T num, char (&buffer)[N], size_t radix) {
		char *out = buffer + N;
		*--out = 0;
		if(num) {
			for(; out != buffer && num; num/=radix) {
				*--out = "0123456789ABCDEFGHIJKLMNOPQRSTYVWXYZabcdefghijklmnopqrstyvwxyz"[num % radix];
			}
		} else {
			*--out='0';
		}
		return out;
	}
};

template<class T,size_t N>
inline char *itoa(T num, char (&buffer)[N], size_t radix=10) {
	return itoa_impl<T,N>::itoa(num,buffer,radix);
}

template<typename T>
std::string to_string(const T& n)
{
	std::ostringstream stream;
	stream << n;
	return stream.str();
}

int64_t perfect_square_root(int64_t x) {
	if(x < 0) return -1;
	if(x < 2) return x;
	int64_t a = x;
	int64_t b = x/2;
	while(a > b) {
		a = b;
		b = (b + x/b)/2;
	}
	if(b*b == x) {
		return b;
	}
	return -1;
}

int64_t perfect_cubic_root(int64_t x) {
	if(x < 0) return -1;
	if(x < 2) return x;
	if(x < 8) return -1;
	int64_t a = x;
	int64_t b = x/3;
	while(a > b) {
		a = b;
		b = (2*b + x/b/b)/3;
	}
	if(b*b*b == x) {
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

template<typename T>
T reverse_digits(T number) {
	T result = 0;
	while(number) {
		result = result*10 + number % 10;
		number /= 10;
	}
	return result;
}

template<class T>
size_t digit_count(T number, uint32_t base=10) {
	if(number == 0) return 1;
	size_t count = 0;
	while(number != 0) {
		++count;
		number /= base;
	}
	return count;
}

std::vector<uint32_t> digit_deconstruct(uint64_t number, uint32_t base=10) {
	std::vector<uint32_t> digits(digit_count(number,base));
	auto i = digits.rbegin();
	while(number) {
		*i++ = number%base;
		number /= base;
	}
	return digits;
}

template<class T>
uint64_t digit_reconstruct(const std::vector<T> &digits, uint32_t base=10) {
	uint64_t number = 0;
	for(auto i=digits.begin();i!=digits.end();i++) {
		number = number*base + *i;
	}
	return number;
}

size_t num_order(size_t number, size_t base=10) {
	size_t order = 1;
	while(number) {
		order *= base;
		number /= base;
	}
	return order;
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
