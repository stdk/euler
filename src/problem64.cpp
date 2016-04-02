#include <iostream>
#include <cstdint>
#include <cmath>
#include <vector>
#include <algorithm>
#include <util.h>

/*
 * Odd period square roots
 */

class sqrt_continued_fraction {
	uint32_t n;
	uint32_t base;
	uint32_t b = 0;
	uint32_t c = 0;
	uint32_t d = 0;
	uint32_t e = 0;
	uint32_t f = 0;

	sqrt_continued_fraction(uint32_t _n, uint32_t _base, uint32_t _b, uint32_t _c)
	:n(_n),base(_base),b(_b),c(_c),
	 d(n - b*b),e(base + b),f(c*e/d) {

	}

public:
	sqrt_continued_fraction(uint32_t _n):n(_n),base(std::floor(std::sqrt(_n))) {

	}

	friend std::ostream& operator<<(std::ostream &os, const sqrt_continued_fraction &s);

	sqrt_continued_fraction& operator++() {
		if(!f) {
			//start continued fractions computing
			*this = sqrt_continued_fraction(n,base,base,1);
			return *this;
		}

		uint32_t next_a = c;
		uint32_t next_b = f*d - b*c;
		uint32_t next_c = d;

		/*
		 * according to analysis next_a is the gcd of next_a,next_b and next_c
		 */

		if(next_b % next_a || next_c % next_a) {
			std::cout << "Looks like we have a failure: " << *this << std::endl;
		}

		*this = sqrt_continued_fraction(n,base,next_b/next_a,next_c/next_a);
		return *this;
	}

	sqrt_continued_fraction operator++(int) {
		sqrt_continued_fraction tmp(*this);
		operator++();
		return tmp;
	}

	uint32_t operator*() const {
		/*
		 * first element of our sequence is base itself
		 * and only after that we start to compute
		 * the actual continued fractions
		 */
		if(f) {
			return f;
		} else {
			return base;
		}
	}

	bool operator==(const sqrt_continued_fraction &o) const {
		return n==o.n && b==o.b && c==o.c;
	}
};

std::ostream& operator<<(std::ostream &os, const sqrt_continued_fraction &s) {
	os << "[N=" << s.n << "][base=" << s.base << "][b=" << s.b
	   << "][c=" << s.c << "][d=" << s.d << "][e=" << s.e
	   << "][f=" << s.f << "]";

	return os;
}

int64_t period_length(uint32_t n) {
	auto perfect = perfect_square_root(n);
	if(perfect != -1) {
		return 0;
	}

	sqrt_continued_fraction initial(n);
	sqrt_continued_fraction current = ++initial;

	for(size_t i=0;;i++) {
		if(++current == initial) {
			return i+1;
		}
	}

	return -1;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	Measure measure;

	size_t count = 0;

	for(uint32_t i=1;i<=10000;i++) {
		auto len = period_length(i);
		if(len % 2 == 1) {
			count++;
		}
	}

	auto passed = measure.passed();
	if(!util::test_mode()) {
		std::cout << "Processing took " << passed << " ms" << std::endl;
		std::cout << "Count: " << count << std::endl;
	} else {
		std::cout << count << std::endl;
	}

	return 0;
}
