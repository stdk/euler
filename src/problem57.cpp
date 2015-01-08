#include <iostream>
#include <gmpxx.h>
#include <util.h>

template<typename T>
class Fraction {
	T p;
	T q;

	static inline size_t digit_count(T n) {
		uint32_t c = 0;
		for(;n;c++,n/=10);
		return c;
	}
public:
	Fraction(T _p,T _q):p(_p),q(_q) {

	}

	inline std::ostream& write(std::ostream &os) const {
		return os << p << "/" << q;
	}

	inline Fraction next() const {
		return Fraction(q,2*q+p);
	}

	inline Fraction operator+(T x) {
		return Fraction(p+x*q,q);
	}

	int32_t digit_number_diff() const {
		int32_t a = digit_count(p);
		int32_t b = digit_count(q);
		return a - b;
	}
};

template<typename T>
std::ostream& operator<<(std::ostream &os, const Fraction<T> &f) {
	return f.write(os);
}

int main(int argc, char **argv) {
	const size_t iterations = 1000;

	Measure measure;

	size_t exceeds = 0;
	Fraction<mpz_class> fraction(0,1);
	for(size_t i=0;i<iterations;i++) {
		auto f = fraction + 1;
		if(f.digit_number_diff() > 0) exceeds += 1;
		//std::cout << i << " -> " << f << std::endl;
		fraction = fraction.next();
	}

	auto passed = measure.passed();
	std::cout << "Search took " << passed << " ms" << std::endl;
	std::cout << "Fractions containing a numerator with more digits than denominator: " << exceeds << std::endl;

	return 0;
}
