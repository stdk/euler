#include <iostream>
#include <gmpxx.h>
#include <fraction.h>
#include <util.h>

template<class T>
int32_t digit_number_diff(T p, T q) {
	int32_t a = digit_count(p);
	int32_t b = digit_count(q);
	return a - b;
}

template<class T>
Fraction<T> next_fraction(Fraction<T> f) {
	return Fraction<T>(f.q(),2*f.q()+f.p());
}

int main(int argc, char **argv) {
	const size_t iterations = 1000;

	Measure measure;

	size_t exceeds = 0;
	Fraction<mpz_class> fraction(0,1);
	for(size_t i=0;i<iterations;i++) {
		auto f = fraction + 1;
		if(digit_number_diff(f.p(),f.q()) > 0) exceeds += 1;
		//std::cout << i << " -> " << f << std::endl;
		fraction = next_fraction(fraction);
	}

	auto passed = measure.passed();
	std::cout << "Search took " << passed << " ms" << std::endl;
	std::cout << "Fractions containing a numerator with more digits than denominator: " << exceeds << std::endl;

	return 0;
}
