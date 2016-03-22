#include <iostream>
#include <cstdint>
#include <cmath>
#include <vector>
#include <algorithm>
#include <primes.h>
#include <util.h>

/*
 * Odd period square roots
 */

template<class T>
struct fraction_t {
	T p;
	T q;

	fraction_t(T _p=0, T _q=0):p(_p),q(_q) {

	}

	fraction_t<T> simplify(const CompactFactors &factors) const {
		auto new_p = p;
		auto new_q = q;
		for(const auto &factor : factors) {
			auto divisor = std::get<0>(factor);
			for(auto i=0;i<std::get<1>(factor);++i) {
				new_p /= divisor;
				new_q /= divisor;
			}
		}

		return fraction_t<T>(new_p,new_q);
	}

	fraction_t<T> simplify(const PrimeNumbers &primes) const {
		auto p_factors = factorize_compact(p,primes);
		auto q_factors = factorize_compact(q,primes);

		auto common_factors = common_compact_factors(p_factors,q_factors);
		if(!common_factors.size()) {
			return *this;
		}

		return simplify(common_factors);
	}

	fraction_t<T> simplify(T value) const {
		return fraction_t<T>(p/value,q/value);
	}

	bool operator==(const fraction_t<T> &other) const {
		return p==other.p && q==other.q;
	}

	bool operator!=(const fraction_t<T> &other) const{
		return p!=other.p || q!=other.q;
	}
};

typedef fraction_t<uint32_t> fraction;

template<class T>
std::ostream& operator<<(std::ostream &os, const fraction_t<T> &fraction) {
	return os << fraction.p << "/" << fraction.q;
}

struct state {
	const PrimeNumbers *primes;

	uint32_t n;
	uint32_t base;
	uint32_t b;
	uint32_t c;
	uint32_t d;
	uint32_t e;
	uint32_t f;
	fraction g;
	fraction h;

	state(const PrimeNumbers *_primes,
		  uint32_t _n)
	:state(_primes,_n,std::floor(std::sqrt(_n)),std::floor(std::sqrt(_n)),1) {

	}

	state(const PrimeNumbers *_primes,
		  uint32_t _n, uint32_t _base, uint32_t _b, uint32_t _c)
	:primes(_primes),
	 n(_n),base(_base),b(_b),c(_c),
	 d(n - b*b),e(base + b),f(c*e/d),
	 g(c,d),h(f*d-b*c,d)
	{

	}

	state next() const {
		auto c_factors = factorize_compact(c,*primes);
		auto d_factors = factorize_compact(d,*primes);
		auto next_b_factors = factorize_compact(h.p,*primes);

		auto factors = common_compact_factors(c_factors,d_factors,next_b_factors);
		//auto i = g.simplify(factors);
		auto j = h.simplify(factors);

		/*if(i.q != j.q) {
			std::cout << "Looks like we have a failure" << i << " " << j << std::endl;
		}*/

		return state(primes,n,base,j.p,j.q);
	}

	bool operator==(const state &o) const {
		return n==o.n && b==o.b && c==o.c;
	}
};

std::ostream& operator<<(std::ostream &os, const state &s) {
	os << "[N=" << s.n << "][base=" << s.base << "][b=" << s.b
	   << "][c=" << s.c << "][d=" << s.d << "][e=" << s.e
	   << "][f=" << s.f << "][g=" << s.g << "][h=" << s.h << "]";

	return os;
}

template<class Primes>
int64_t period_length(uint32_t n,const Primes &primes) {
	auto perfect = perfect_square_root(n);
	if(perfect != -1) {
		return 0;
	}

	state initial(&primes,n);
	state current = initial;

	for(size_t i=0;;i++) {
		//std::cout << current << std::endl;
		current = current.next();

		if(current == initial) {
			return i+1;
		}
	}

	std::cout << "Processing of n = " << n << " reached iteration limit" << std::endl;

	return -1;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	const prime_t limit = 100000;

	Measure measure;
	const auto &primes = PrimeNumbers(limit);
	auto passed = measure.passed();
	if(!util::test_mode) {
		std::cout << "Prime generation took " << passed << " ms" << std::endl;
	}

	measure.reset();

	size_t count = 0;

	for(uint32_t i=1;i<=10000;i++) {
		auto len = period_length(i,primes);
		if(len % 2 == 1) {
			count++;
		}
	}

	passed = measure.passed();
	if(!util::test_mode) {
		std::cout << "Processing took " << passed << " ms" << std::endl;
		std::cout << "Count: " << count << std::endl;
	} else {
		std::cout << count << std::endl;
	}

	return 0;
}
