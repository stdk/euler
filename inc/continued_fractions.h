#ifndef CONTINUED_FRACTIONS_H
#define CONTINUED_FRACTIONS_H

#include <cmath>
#include <iostream>
#include <cstdint>
#include <array>
#include <fraction.h>

class sqrt_terms_iterator {
    uint32_t n;
    uint32_t base;
    uint32_t b = 0;
    uint32_t c = 0;
    uint32_t d = 0;
    uint32_t e = 0;
    uint32_t f = 0;

    sqrt_terms_iterator(uint32_t _n, uint32_t _base, uint32_t _b, uint32_t _c)
    :n(_n),base(_base),b(_b),c(_c),
     d(n - b*b),e(base + b),f(c*e/d) {

    }

public:
    sqrt_terms_iterator(uint32_t _n):n(_n),base(std::floor(std::sqrt(_n))) {

    }

    friend std::ostream& operator<<(std::ostream &os, const sqrt_terms_iterator &s);

    sqrt_terms_iterator& operator++() {
        if(!f) {
            //start continued fractions computing
            *this = sqrt_terms_iterator(n,base,base,1);
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

        *this = sqrt_terms_iterator(n,base,next_b/next_a,next_c/next_a);
        return *this;
    }

    sqrt_terms_iterator operator++(int) {
        sqrt_terms_iterator tmp(*this);
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

    bool operator==(const sqrt_terms_iterator &o) const {
        return n==o.n && b==o.b && c==o.c;
    }
};

std::ostream& operator<<(std::ostream &os, const sqrt_terms_iterator &s) {
    os << "[N=" << s.n << "][base=" << s.base << "][b=" << s.b
       << "][c=" << s.c << "][d=" << s.d << "][e=" << s.e
       << "][f=" << s.f << "]";

    return os;
}

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
        k = {approximation.q(), k[0]};
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

#endif //CONTINUED_FRACTIONS_H
