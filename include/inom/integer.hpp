#pragma once

#include <ostream>
#include <type_traits>
#include <algorithm>
#include <limits>
#include <cstdint>
#include "detail/repr_for.hpp"
#include "detail/strtoi.hpp"
#include "detail/constexpr.hpp"

namespace inom {

using range_t = std::intmax_t;

template<range_t L, range_t R>
class integer;

template<typename Integer>
using inferred_integer =
    integer<
        std::numeric_limits<Integer>::min(),
        std::numeric_limits<Integer>::max()
    >;

template<range_t L, range_t R = L>
class integer {
private:

    // aliases
    using data_t = range_t;
    using offset_t = 
        typename detail::repr_for<
            detail::abs(R - L)
        >::type;

    // attributes
    static constexpr range_t pivot = L;
    offset_t offset;

    // conversion
    data_t to_data(offset_t offset) const { return pivot + offset; }
    offset_t to_offset(data_t data) const { return data - pivot; }

    // constructors
    explicit integer(data_t data) 
        : offset(to_offset(data)) {}
    
    // friend declarations
    template<data_t I>
    friend integer<I> make_int();

    template<
        typename Integer,
        std::enable_if_t<
            (  std::numeric_limits<Integer>::is_integer
            && std::is_convertible<
                Integer, typename inferred_integer<Integer>::data_t
            >::value )
        , int>
    >
    friend inferred_integer<Integer> from_int(Integer);
    
    template<range_t A, range_t B>
    friend class integer;
    
public:

    // bounds
    static constexpr range_t lbound = L;
    static constexpr range_t rbound = R;

    // arithmetic operations
    template<range_t OL, range_t OR>
    auto operator+(integer<OL, OR> const& rhs) {
        return integer<L + OL, R + OR>(data() + rhs.data());
    }
    
    template<range_t OL, range_t OR>
    auto operator-(integer<OL, OR> const& rhs) {
        return integer<L - OR, R - OL>(data() - rhs.data());
    }

    template<range_t OL, range_t OR>
    auto operator*(integer<OL, OR> const& rhs) {
        return integer<
            detail::min(L * OL, L * OR, R * OL, R * OR), 
            detail::max(L * OL, L * OR, R * OL, R * OR)
        >(data() * rhs.data());
    }

    // default constructor (0-initialization)
    template<
        bool B = (L <= 0 && R >= 0),
        typename std::enable_if<B, int>::type = 0
    >
    integer() : integer(0) {}
    
    // copy and move constructors
    template<
        data_t A, data_t B,
        typename std::enable_if<(L <= A && R >= B), int>::type = 0
    >
    integer(integer<A, B> const& o) : integer(o.data()) {}
    integer(integer const&) = default;
    integer(integer&&) = default;
    
    // copy and move assignments
    template<
        data_t A, data_t B,
        typename std::enable_if<(A <= L && B >= R), int>::type = 0
    >
    integer& operator=(integer<A, B> const& o) { 
        offset = to_offset(o.data()); 
    }
    integer& operator=(integer const&) = default;
    integer& operator=(integer&&) = default;

    // data access
    data_t data() const { 
        return to_data(offset); 
    }

};

// short alias
template<range_t L, range_t R = L>
using i = integer<L, R>;

// single value constructor
template<range_t I>
integer<I> make_int() {
    return integer<I>(I);
}

// inferred integer construction
template<
    typename Integer,
    std::enable_if_t<
        (  std::numeric_limits<Integer>::is_integer
        && std::is_convertible<
            Integer, typename inferred_integer<Integer>::data_t
        >::value )
        , int> = 0
>
inferred_integer<Integer> from_int(const Integer& i) {
    return inferred_integer<Integer>(i);
}

// literals
namespace literals {

template <char... Chars>
integer<detail::strtoi<Chars...>::value> 
operator "" _int() {
    constexpr range_t I = detail::strtoi<Chars...>::value;
    return make_int<I>();
}

} // namespace literals

// arithmetic operations
template<range_t A, range_t B>
auto operator-(integer<A, B> const& a) {
    using namespace literals;
    return 0_int - a;
}

// comparison operations
template<range_t A, range_t B, range_t C, range_t D>
bool operator==(integer<A, B> const& a, integer<C, D> const& b) {
    return a.data() == b.data();
}

template<range_t A, range_t B, range_t C, range_t D>
bool operator!=(integer<A, B> const& a, integer<C, D> const& b) {
    return !(a == b); 
}

template<range_t A, range_t B, range_t C, range_t D>
bool operator<(integer<A, B> const& a, integer<C, D> const& b) {
    return a.data() < b.data();
}

template<range_t A, range_t B, range_t C, range_t D>
bool operator<=(integer<A, B> const& a, integer<C, D> const& b) {
    return a.data() <= b.data();
}

template<range_t A, range_t B, range_t C, range_t D>
bool operator>(integer<A, B> const& a, integer<C, D> const& b) {
    return a.data() > b.data();
}

template<range_t A, range_t B, range_t C, range_t D>
bool operator>=(integer<A, B> const& a, integer<C, D> const& b) {
    return a.data() >= b.data();
}

// printing operations
template<range_t A, range_t B>
std::ostream& operator<<(std::ostream& os, integer<A, B> const& x) {
    return (os << x.data());
}

} // namespace inom
