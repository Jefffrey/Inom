#pragma once

#include <type_traits>

namespace inom {
namespace detail {

// conversion between a char in octal
// representation and the corresponding integer
template<char C, class Enable = void>
struct octal_repr;

template<char C>
struct octal_repr<
    C,
    typename std::enable_if<
        C >= '0' && C <= '7'
    >::type
> {
    static constexpr std::uintmax_t value = C - '0';
};

// conversion between a char in decimal
// representation and the corresponding integer
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

// conversion between a char in hexadecimal
// representation and the corresponding integer
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

// conversion between a char in binary
// representation and the corresponding integer
template<char>
struct binary_repr;

template<>
struct binary_repr<'0'> {
    static constexpr std::uintmax_t value = 0;
};

template<>
struct binary_repr<'1'> {
    static constexpr std::uintmax_t value = 1;
};

// implementation for conversion between
// number strings and integers
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

// exported `strtoi` with representation detection between
// binary, octal, decimal, hexadecimal representations
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

template<char Head, char... Number>
struct strtoi<'0', 'b', Head, Number...> {
    static constexpr std::intmax_t value = 
        str_base<binary_repr, 2, Head, Number...>::value;
};

template<char Head, char... Number>
struct strtoi<'0', Head, Number...> {
    static constexpr std::intmax_t value = 
        str_base<octal_repr, 8, Head, Number...>::value;
};

} // namespace detail
} // namespace inom
