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

CompactFactors common_compact_factors(const CompactFactors &a, const CompactFactors &b) {
	CompactFactors common_factors;

	auto i = a.begin();
	auto j = b.begin();

	while(i!=a.end() && j != b.end()) {

		auto x = std::get<0>(*i);
		auto y = std::get<0>(*j);

		if(x == y) {
			auto count = std::min(std::get<1>(*i),std::get<1>(*j));
			common_factors.push_back(std::make_tuple(x,count));
			++i;
			++j;
		} else if(x < y) {
			++i;
		} else if(x > y) {
			++j;
		}

	}

	return common_factors;
}

CompactFactors common_compact_factors(const CompactFactors &a,
                                      const CompactFactors &b,
                                      const CompactFactors &c) {
	CompactFactors common_factors;

	auto i = a.begin();
	auto j = b.begin();
	auto k = c.begin();

	while(i != a.end() && j != b.end() && k != c.end()) {
		auto x = std::get<0>(*i);
		auto y = std::get<0>(*j);
		auto z = std::get<0>(*k);

		if(x == y && y == z) {
			auto count = std::min({std::get<1>(*i),
				                   std::get<1>(*j),
								   std::get<1>(*k)});
			common_factors.push_back(std::make_tuple(x,count));
			++i;
			++j;
			++k;
		} else if(x <= y && x <= z) {
			++i;
		} else if(y <= x && y <= z) {
			++j;
		} else if(z <= x && z <= y) {
			++k;
		}
	}

	return common_factors;
}

std::ostream& operator<<(std::ostream &os, const CompactFactor &factor) {
	return os << std::get<0>(factor) << "^" << std::get<1>(factor);
}

std::ostream& operator<<(std::ostream &os, const CompactFactors &factors) {
	os << "[";
	for(auto i=factors.begin();i!=factors.end();++i) {
		os << *i << (i == factors.end()-1 ? "" : " * ");
	}
	os << "]";

	return os;
}

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

constexpr double E = 1e-10;
constexpr size_t MAX_ITERATIONS = 1000000;

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
int64_t period_length2(uint32_t n,const Primes &primes) {
	auto perfect = perfect_square_root(n);
	if(perfect != -1) {
		//std::cout << n << " is a perfect square of " << perfect << std::endl;
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

int64_t period_length(uint32_t n) {
	std::vector<uint32_t> sequence;

	auto perfect = perfect_square_root(n);
	if(perfect != -1) {
		std::cout << n << " is a perfect square of " << perfect << std::endl;
		return 0;
	}

	double x = std::sqrt(n);

	uint32_t a = std::floor(x);
	x -= a;

	double initial_x = x;

	for(size_t i=1;;++i) {
		x = 1/x;
		a = std::floor(x);
		sequence.push_back(a);
		x -= a;

		if(i % 2 == 0) {
			//auto end = sequence.begin()+i/2;
			std::cout << "initial_x - x = " << std::abs(initial_x-x) << std::endl;
			if(std::abs(initial_x - x) < E /*&&
				std::equal(sequence.begin(),end,end)*/) {
				std::cout << n << ":len = " << i/2 << std::endl;
				/*std::cout << n << " -> (";
				for(auto e=sequence.begin();e!=end;++e) {
					std::cout << *e << (e==end-1 ? "" : ",");
				}
				std::cout << ")" << std::endl;*/


				return i/2;
			}
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
	std::cout << "Prime generation took " << passed << " ms" << std::endl;

	measure.reset();

	size_t count = 0;

	//fraction f(100,50);

	//std::cout << f << "->" << f.simplify(primes) << std::endl;

	for(uint32_t i=1;i<=10000;i++) {
		auto len = period_length2(i,primes);
		//std::cout << "Length: " << len << std::endl;
		if(len % 2 == 1) {
			count++;
		}
	}

	passed = measure.passed();
	std::cout << "Processing took " << passed << " ms" << std::endl;
	std::cout << "Count: " << count << std::endl;

	return 0;
}
