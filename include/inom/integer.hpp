#pragma once

#include <ostream>
#include <type_traits>
#include "util.hpp"

namespace inom {

using detail::max_n;

template<max_n F, max_n T = F>
class integer {
public:
    using repr_t = 
        typename detail::repr_for<
            detail::constexpr_abs(T - F)
        >::type;
    static constexpr max_n pivot = F;
private:
    repr_t repr;
    
    integer(repr_t i) : repr(i) {}
    
    template<max_n I>
    friend integer<I, I> make_int();
    
    template<max_n A, max_n B>
    friend class integer;
    
    template<max_n A, max_n B, max_n C, max_n D>
    friend integer<A + C, B + D> operator+(integer<A, B> const&, integer<C, D> const&);
    
    template<max_n A, max_n B, max_n C, max_n D>
    friend integer<A - C, B - D> operator-(integer<A, B> const&, integer<C, D> const&);

    template<max_n A, max_n B>
    friend std::ostream& operator<<(std::ostream&, integer<A, B> const&);
public:

    integer() : repr(-F) {}
    
    template<
        max_n A, max_n B,
        typename std::enable_if<(F <= A && T >= B), int>::type = 0
    >
    integer(integer<A, B> const& o) : repr(o.repr + (integer<A, B>::pivot - pivot)) {}
    integer(integer const&) = default;
    integer(integer&&) = default;
    
    template<
        max_n A, max_n B,
        typename std::enable_if<(A <= F && B >= T), int>::type = 0
    >
    integer& operator=(integer<A, B> const& o) { repr = o.repr + (pivot - integer<A, B>::pivot); }
    integer& operator=(integer const&) = default;
    integer& operator=(integer&&) = default;

    repr_t data() const { return pivot + repr; }
};

template<max_n I>
integer<I, I> make_int() {
    return integer<I, I>(0);
}

template<max_n A, max_n B, max_n C, max_n D>
integer<A + C, B + D> operator+(integer<A, B> const& a, integer<C, D> const& b) {
    return integer<A + C, B + D>(a.repr + b.repr);
}

template<max_n A, max_n B, max_n C, max_n D>
integer<A - D, B - C> operator-(integer<A, B> const& a, integer<C, D> const& b) {
    return integer<A - D, B - C>(a.repr - b.repr);
}

template<max_n A, max_n B, max_n C, max_n D>
bool operator==(integer<A, B> const& a, integer<C, D> const& b) {
    return a.data() == b.data();
}

template<max_n A, max_n B, max_n C, max_n D>
bool operator!=(integer<A, B> const& a, integer<C, D> const& b) {
    return !(a == b); 
}

template<max_n A, max_n B>
std::ostream& operator<<(std::ostream& os, integer<A, B> const& x) {
    return (os << (integer<A, B>::pivot + x.repr));
}

} // namespace inom
