#ifndef FRACTION_H_
#define FRACTION_H_

#include <iostream>
#include <util.h>

template<typename T>
class Fraction {
	T _p;
	T _q;
public:
	Fraction(T p,T q):_p(p),_q(q) {

	}

	template<typename X>
	Fraction(Fraction<X> &&f):
	_p(static_cast<T>(f.p())),_q(static_cast<T>(f.q())) {

	}

	inline T p() const {
		return _p;
	}

	inline T q() const {
		return _q;
	}

	inline std::ostream& write(std::ostream &os) const {
		return os << _p << "/" << _q;
	}

	Fraction<T> simplify() const {
		T divisor = gcd(_p,_q);

		if(divisor != 1) {
			return Fraction<T>(_p/divisor,_q/divisor);
		}

		return *this;
	}

	inline Fraction operator+(T x) const {
		return Fraction(_p+x*_q,_q);
	}

	inline Fraction operator+(const Fraction &o) const {
		return Fraction(_p*o._q + _q*o._p,_q*o._q).simplify();
	}

	inline Fraction operator-(const Fraction &o) const {
		return Fraction(_p*o._q - _q*o._p,_q*o._q).simplify();
	}

	inline bool operator<(T x) const {
		return _p < _q*x;
	}

	inline bool operator>(T x) const {
		return _p > _q*x;
	}

	inline bool operator<(const Fraction &o) const {
		return _p*o._q < _q*o._p;
	}

	inline bool operator>(const Fraction &o) const {
		return _p*o._q > _q*o._p;
	}
};

template<typename T>
std::ostream& operator<<(std::ostream &os, const Fraction<T> &f) {
	return f.write(os);
}

#endif /* FRACTION_H_ */
