#pragma once

#include "../aliases.hpp"
#include <type_traits>

namespace inom {
namespace detail {

template<char C, class Enable = void>
struct decimal_repr;

template<char C>
struct decimal_repr<
    C,
    typename std::enable_if<
        C >= '0' && C <= '9'
    >::type
> {
    static constexpr std::uintmax_t value = C - '0';
};

template<char, class Enable = void>
struct hex_repr;

template<char C>
struct hex_repr<
    C,
    typename std::enable_if<
        C >= '0' && C <= '9'
    >::type
> {
    static constexpr std::uintmax_t value = C - '0';
};

template<char C>
struct hex_repr<
    C,
    typename std::enable_if<
        C >= 'a' && C <= 'f'
    >::type
>
{
    static constexpr std::uintmax_t value = C - 'a' + 10;
};

template<
    template<char, typename...> class, 
    std::uintmax_t, std::uintmax_t, 
    char...
>
struct str_base_impl;

template<
    template<char, typename...> class ReprFn, 
    std::uintmax_t Base, 
    std::uintmax_t Rest, 
    char Last
>
struct str_base_impl<ReprFn, Base, Rest, Last> {
    static constexpr std::uintmax_t value = 
        Rest + ReprFn<Last>::value;
};

template<
    template<char, typename...> class ReprFn, 
    std::uintmax_t Base, 
    std::uintmax_t Rest, 
    char Head, 
    char... Tail
>
struct str_base_impl<ReprFn, Base, Rest, Head, Tail...> {
    static constexpr std::uintmax_t value = 
        str_base_impl<
            ReprFn, Base, 
            (Rest + ReprFn<Head>::value) * Base, 
            Tail...
        >::value;
};

template<template<char, typename...> class ReprFn, std::uintmax_t Base, char... Str>
struct str_base {
    static constexpr std::intmax_t value =
        str_base_impl<ReprFn, Base, 0, Str...>::value;
};

template<char Head, char... Number>
struct strtoi {
    static constexpr std::intmax_t value = 
        str_base<decimal_repr, 10, Head, Number...>::value;
};

template<char Head, char... Number>
struct strtoi<'0', 'x', Head, Number...> {
    static constexpr std::intmax_t value = 
        str_base<hex_repr, 16, Head, Number...>::value;
};

} // namespace detail
} // namespace inom
