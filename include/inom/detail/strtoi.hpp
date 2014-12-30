#pragma once

#include "../aliases.hpp"

namespace inom {
namespace detail {

template<std::uintmax_t, char...>
struct strtoi_impl;

template<std::uintmax_t Rest, char Last>
struct strtoi_impl<Rest, Last> {
    static constexpr std::uintmax_t value = Rest + (Last - '0');
};

template<std::uintmax_t Rest, char Head, char... Tail>
struct strtoi_impl<Rest, Head, Tail...> {
    static constexpr std::uintmax_t value = 
        strtoi_impl<(Rest + (Head - '0')) * 10, Tail...>::value;
};

template<char... Number>
struct strtoi {
    static constexpr std::intmax_t value = 
        strtoi_impl<0, Number...>::value;
};

} // namespace detail
} // namespace inom
