#ifndef FRACTION_H_
#define FRACTION_H_

#include <iostream>

template<typename T>
class Fraction {
	T _p;
	T _q;
public:
	Fraction(T p,T q):_p(p),_q(q) {

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

	inline Fraction operator+(T x) {
		return Fraction(_p+x*_q,_q);
	}
};

template<typename T>
std::ostream& operator<<(std::ostream &os, const Fraction<T> &f) {
	return f.write(os);
}

#endif /* FRACTION_H_ */
