#pragma once

#include <ostream>
#include <type_traits>
#include "aliases.hpp"
#include "detail/repr_for.hpp"
#include "detail/constexpr.hpp"

namespace inom {

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
    friend integer<I, I> make_int();
    
    template<data_t A, data_t B>
    friend class integer;
    
    template<data_t A, data_t B, data_t C, data_t D>
    friend integer<A + C, B + D> operator+(integer<A, B> const&, integer<C, D> const&);
    
    template<data_t A, data_t B, data_t C, data_t D>
    friend integer<A - D, B - C> operator-(integer<A, B> const&, integer<C, D> const&);

    template<data_t A, data_t B>
    friend std::ostream& operator<<(std::ostream&, integer<A, B> const&);
public:

    template<
        bool B = (L <= 0 && R >= 0),
        typename std::enable_if<B, int>::type = 0
    >
    integer() : integer(0) {}
    
    template<
        data_t A, data_t B,
        typename std::enable_if<(L <= A && R >= B), int>::type = 0
    >
    integer(integer<A, B> const& o) : integer(o.data()) {}
    integer(integer const&) = default;
    integer(integer&&) = default;
    
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

template<intdata_t I>
integer<I, I> make_int() {
    return integer<I, I>(I);
}

template<intdata_t A, intdata_t B, intdata_t C, intdata_t D>
integer<A + C, B + D> operator+(integer<A, B> const& a, integer<C, D> const& b) {
    return integer<A + C, B + D>(a.data() + b.data());
}

template<intdata_t A, intdata_t B, intdata_t C, intdata_t D>
integer<A - D, B - C> operator-(integer<A, B> const& a, integer<C, D> const& b) {
    return integer<A - D, B - C>(a.data() - b.data());
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
