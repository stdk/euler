#ifndef FRACTION_H_
#define FRACTION_H_

#include <iostream>
#include <limits>
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

    static Fraction<T> read(const std::string &s) {
        Fraction<T> fraction(0,1);

        std::size_t pos = 0;
        fraction._p = std::stoul(s,&pos,0);

        if(pos && s[pos]=='/') {
            std::size_t pos2 = 0;
            fraction._q = std::stoul(s.c_str()+pos+1,&pos2,0);
        }

        return fraction;
    }

    inline std::istream& read(std::istream &is) {
        std::string s;
        is >> s;

        *this = read(s);

        return is;
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

    inline explicit operator double() const {
        if(!_q) {
            if(_p >= 0) {
                return std::numeric_limits<double>::infinity();
            } else {
                return -std::numeric_limits<double>::infinity();
            }
        }
        return static_cast<double>(_p)/_q;
    }

    inline explicit operator float() const {
        if(!_q) {
            if(_p >= 0) {
                return std::numeric_limits<float>::infinity();
            } else {
                return -std::numeric_limits<float>::infinity();
            }
        }
        return static_cast<float>(_p)/_q;
    }
};

template<typename T>
std::ostream& operator<<(std::ostream &os, const Fraction<T> &f) {
    return f.write(os);
}

template<typename T>
std::istream& operator>>(std::istream &is, Fraction<T> &f) {
    return f.read(is);
}

#endif /* FRACTION_H_ */
