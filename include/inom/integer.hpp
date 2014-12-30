#pragma once

#include <ostream>
#include <type_traits>
#include "util.hpp"

namespace inom {

using detail::max_n;

namespace detail {

    constexpr max_n offset_to_data(max_n pivot, max_n offset) {
        return pivot + offset;
    }

    constexpr max_n data_to_offset(max_n pivot, max_n data) {
        return data - pivot;
    }

}

template<max_n F, max_n T = F>
class integer {
public:
    using repr_t = 
        typename detail::repr_for<
            detail::constexpr_abs(T - F)
        >::type;
    static constexpr max_n pivot = F;
private:
    repr_t offset;
    
    explicit integer(max_n data) 
        : offset(detail::data_to_offset(pivot, data)) {}
    
    template<max_n I>
    friend integer<I, I> make_int();
    
    template<max_n A, max_n B>
    friend class integer;
    
    template<max_n A, max_n B, max_n C, max_n D>
    friend integer<A + C, B + D> operator+(integer<A, B> const&, integer<C, D> const&);
    
    template<max_n A, max_n B, max_n C, max_n D>
    friend integer<A - D, B - C> operator-(integer<A, B> const&, integer<C, D> const&);

    template<max_n A, max_n B>
    friend std::ostream& operator<<(std::ostream&, integer<A, B> const&);
public:

    template<
        bool B = (F <= 0 && T >= 0),
        typename std::enable_if<B, int>::type = 0
    >
    integer() : integer(0) {}
    
    template<
        max_n A, max_n B,
        typename std::enable_if<(F <= A && T >= B), int>::type = 0
    >
    integer(integer<A, B> const& o) : integer(o.data()) {}
    integer(integer const&) = default;
    integer(integer&&) = default;
    
    template<
        max_n A, max_n B,
        typename std::enable_if<(A <= F && B >= T), int>::type = 0
    >
    integer& operator=(integer<A, B> const& o) { 
        offset = detail::data_to_offset(pivot, o.data()); 
    }

    integer& operator=(integer const&) = default;
    integer& operator=(integer&&) = default;

    max_n data() const { 
        return detail::offset_to_data(pivot, offset); 
    }
};

template<max_n I>
integer<I, I> make_int() {
    return integer<I, I>(I);
}

template<max_n A, max_n B, max_n C, max_n D>
integer<A + C, B + D> operator+(integer<A, B> const& a, integer<C, D> const& b) {
    return integer<A + C, B + D>(a.data() + b.data());
}

template<max_n A, max_n B, max_n C, max_n D>
integer<A - D, B - C> operator-(integer<A, B> const& a, integer<C, D> const& b) {
    return integer<A - D, B - C>(a.data() - b.data());
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
    return (os << x.data());
}

} // namespace inom
