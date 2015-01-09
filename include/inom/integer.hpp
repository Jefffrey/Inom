#pragma once

#include <ostream>
#include <type_traits>
#include <algorithm>
#include <limits>
#include "aliases.hpp"
#include "detail/repr_for.hpp"
#include "detail/strtoi.hpp"
#include "detail/constexpr.hpp"

namespace inom {

namespace detail {

    constexpr intdata_t mul_min(
        intdata_t a, intdata_t b, 
        intdata_t c, intdata_t d
    ) {
        return min(a * c, a * d, b * c, b * d);
    }

    constexpr intdata_t mul_max(
        intdata_t a, intdata_t b, 
        intdata_t c, intdata_t d
    ) {
        return max(a * c, a * d, b * c, b * d);
    }

} // namespace detail

template<intdata_t L, intdata_t R>
class integer;

template<typename Integer>
using inferred_integer =
    integer<
        std::numeric_limits<Integer>::min(),
        std::numeric_limits<Integer>::max()
    >;

template<intdata_t L, intdata_t R = L>
class integer {
public:
    using data_t = intdata_t;
    static constexpr data_t lbound = L;
    static constexpr data_t rbound = R;
private:
    using offset_t = 
        typename detail::repr_for<
            detail::abs(R - L)
        >::type;
    static constexpr data_t pivot = L;

    data_t to_data(offset_t offset) const { return pivot + offset; }
    data_t to_offset(data_t data) const { return data - pivot; }

    offset_t offset;
    
    explicit integer(data_t data) 
        : offset(to_offset(data)) {}
    
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
    friend inferred_integer<Integer> from_int(const Integer&);
    
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

    // Default constructor (0-initialization)
    template<
        bool B = (L <= 0 && R >= 0),
        typename std::enable_if<B, int>::type = 0
    >
    integer() : integer(0) {}
    
    // Copy and move constructors
    template<
        data_t A, data_t B,
        typename std::enable_if<(L <= A && R >= B), int>::type = 0
    >
    integer(integer<A, B> const& o) : integer(o.data()) {}
    integer(integer const&) = default;
    integer(integer&&) = default;
    
    // Copy and move assignments
    template<
        data_t A, data_t B,
        typename std::enable_if<(A <= L && B >= R), int>::type = 0
    >
    integer& operator=(integer<A, B> const& o) { 
        offset = to_offset(o.data()); 
    }
    integer& operator=(integer const&) = default;
    integer& operator=(integer&&) = default;

    data_t data() const { 
        return to_data(offset); 
    }
};

template<intdata_t L, intdata_t R = L>
using i = integer<L, R>;

template<intdata_t I>
integer<I> make_int() {
    return integer<I>(I);
}

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

namespace literals {

template <char... Chars>
integer<detail::strtoi<Chars...>::value> 
operator "" _int() {
    constexpr intdata_t I = detail::strtoi<Chars...>::value;
    return make_int<I>();
}

} // namespace literals

template<intdata_t A, intdata_t B, intdata_t C, intdata_t D>
integer<A + C, B + D> operator+(integer<A, B> const& a, integer<C, D> const& b) {
    return integer<A + C, B + D>(a.data() + b.data());
}

template<intdata_t A, intdata_t B, intdata_t C, intdata_t D>
integer<A - D, B - C> operator-(integer<A, B> const& a, integer<C, D> const& b) {
    return integer<A - D, B - C>(a.data() - b.data());
}

template<intdata_t A, intdata_t B, intdata_t C, intdata_t D>
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

template<intdata_t A, intdata_t B>
auto operator-(integer<A, B> const& a) {
    using namespace literals;
    return 0_int - a;
}

template<intdata_t A, intdata_t B, intdata_t C, intdata_t D>
bool operator==(integer<A, B> const& a, integer<C, D> const& b) {
    return a.data() == b.data();
}

template<intdata_t A, intdata_t B, intdata_t C, intdata_t D>
bool operator!=(integer<A, B> const& a, integer<C, D> const& b) {
    return !(a == b); 
}

template<intdata_t A, intdata_t B>
std::ostream& operator<<(std::ostream& os, integer<A, B> const& x) {
    return (os << x.data());
}

} // namespace inom
