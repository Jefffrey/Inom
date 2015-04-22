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

namespace detail {

    constexpr range_t mul_min(
        range_t a, range_t b, 
        range_t c, range_t d
    ) {
        return min(a * c, a * d, b * c, b * d);
    }

    constexpr range_t mul_max(
        range_t a, range_t b, 
        range_t c, range_t d
    ) {
        return max(a * c, a * d, b * c, b * d);
    }

} // namespace detail

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
public:
    // bounds
    static constexpr range_t lbound = L;
    static constexpr range_t rbound = R;
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
    
    template<data_t A, data_t B>
    friend class integer;
    
    template<data_t A, data_t B, data_t C, data_t D>
    friend integer<A + C, B + D> operator+(integer<A, B> const&, integer<C, D> const&);
    
    template<data_t A, data_t B, data_t C, data_t D>
    friend integer<A - D, B - C> operator-(integer<A, B> const&, integer<C, D> const&);

    template<data_t A, data_t B, data_t C, data_t D>
    friend integer<
        detail::mul_min(A, B, C, D), 
        detail::mul_max(A, B, C, D)
    > operator*(integer<A, B> const&, integer<C, D> const&);

    template<data_t A, data_t B>
    friend std::ostream& operator<<(std::ostream&, integer<A, B> const&);
public:

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
template<range_t A, range_t B, range_t C, range_t D>
integer<A + C, B + D> operator+(integer<A, B> const& a, integer<C, D> const& b) {
    return integer<A + C, B + D>(a.data() + b.data());
}

template<range_t A, range_t B, range_t C, range_t D>
integer<A - D, B - C> operator-(integer<A, B> const& a, integer<C, D> const& b) {
    return integer<A - D, B - C>(a.data() - b.data());
}

template<range_t A, range_t B, range_t C, range_t D>
integer<
    detail::mul_min(A, B, C, D), 
    detail::mul_max(A, B, C, D)
>
operator*(integer<A, B> const& a, integer<C, D> const& b) {
    return integer<
        detail::mul_min(A, B, C, D), 
        detail::mul_max(A, B, C, D)
    >(a.data() * b.data());
}

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

// printing operations
template<range_t A, range_t B>
std::ostream& operator<<(std::ostream& os, integer<A, B> const& x) {
    return (os << x.data());
}

} // namespace inom
