#include <cppformat/format.h>
#include <cstdint>
#include <gmpxx.h>
#include <fraction.h>
#include <util.h>

class e_terms_iterator {
	uint32_t n = 0;
public:
	e_terms_iterator(uint32_t _n=0):n(_n)  {

	}

    inline e_terms_iterator& operator++() noexcept {
        ++n;
        return *this;
    }

    inline e_terms_iterator operator++(int) noexcept {
    	e_terms_iterator tmp(*this);
        operator++();
        return tmp;
    }

    inline e_terms_iterator& operator--() noexcept {
        --n;
        return *this;
    }

    inline e_terms_iterator operator--(int) noexcept {
    	e_terms_iterator tmp(*this);
        operator--();
        return tmp;
    }

    inline e_terms_iterator operator+(int32_t x) noexcept {
    	if(x < 0 && std::abs(x) > n) {
    		return e_terms_iterator(0);
    	}
    	return e_terms_iterator(n+x);
    }

    inline e_terms_iterator operator-(int32_t x) noexcept {
		if(x > 0 && std::abs(x) > n) {
			return e_terms_iterator(0);
		}
		return e_terms_iterator(n-x);
	}

    inline bool operator<(const e_terms_iterator &other) noexcept{
    	return n < other.n;
    }

    inline bool operator>(const e_terms_iterator &other) noexcept{
		return n > other.n;
	}

    inline bool operator<=(const e_terms_iterator &other) noexcept{
		return n <= other.n;
	}

	inline bool operator>=(const e_terms_iterator &other) noexcept{
		return n >= other.n;
	}

	inline bool operator==(const e_terms_iterator &other) noexcept{
		return n == other.n;
	}

	inline bool operator!=(const e_terms_iterator &other) noexcept{
		return n != other.n;
	}

    inline uint32_t operator*() noexcept {
    	if(0 == n) {
    		return 2;
    	} else {
    		switch(n % 3) {
    		case 0:
    		case 1:
    			return 1;
    		case 2:
    			return (n/3+1)*2;
    		}
    	}
    	return 0;
    }
};

template<class T,class I>
class approximation_iterator_t {
	I term;
	std::array<T,2> h;
	std::array<T,2> k;
	Fraction<T> approximation;
public:
	approximation_iterator_t(I terms_iterator)
	:term(terms_iterator),h({1,0}),k({0,1}),approximation(*term,1) {

	}

    inline approximation_iterator_t& operator++() {
    	++term;
    	h = {approximation.p(), h[0]};
    	k = {approximation.q(), h[1]};
    	approximation = Fraction<T>(*term*h[0]+h[1],*term*k[0]+k[1]);

        return *this;
    }

    inline approximation_iterator_t operator++(int) {
    	approximation_iterator_t tmp(*this);
        operator++();
        return tmp;
    }

    inline approximation_iterator_t operator+(uint32_t x) const {
    	approximation_iterator_t tmp(*this);
    	for(auto i=0u;i<x;++i) ++tmp;
    	return tmp;
    }

    inline approximation_iterator_t& operator+=(uint32_t x) {
		for(auto i=0u;i<x;++i) operator++();
		return *this;
	}

	inline bool operator==(const approximation_iterator_t &other) const {
		return term == other.term;
	}

	inline bool operator!=(const approximation_iterator_t &other) const {
		return term != other.term;
	}

	inline const Fraction<T>* operator->() const {
		return &approximation;
	}

    inline Fraction<T> operator*() const {
    	return approximation;
    }
};

template<class T, class I>
auto approximation_iterator(I terms_iterator) -> decltype(approximation_iterator_t<T,I>(terms_iterator)) {
	return approximation_iterator_t<T,I>(terms_iterator);
}

int main() {
	std::ios_base::sync_with_stdio(false);

	Measure measure;

	auto approximation = approximation_iterator<mpz_class>(e_terms_iterator());
	approximation += 99; //to get 100th approximation

	auto str = approximation->p().get_str();
	auto sum = std::accumulate(str.begin(), str.end(), (size_t)0, [](size_t a, size_t b) {
		return a + b - 0x30;
	});

	auto passed = measure.passed();

	if(!util::test_mode()) {
		fmt::print("Processing toook {} ms\n", passed);
		fmt::print("Digit sum in final approximation: ");
	}
	fmt::print("{}\n",sum);

	return 0;
}
