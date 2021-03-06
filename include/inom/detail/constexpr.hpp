#pragma once

#include <cinttypes>
#include <functional>

namespace inom {
namespace detail {

constexpr std::intmax_t abs(std::intmax_t n) {
    return (n >= 0) ? n : -n; 
}

template<typename Int>
constexpr Int power(Int x, unsigned int y) {
    if(y == 0) return 1;

    Int sub = power(x, y / 2);
    if (y % 2 == 0) return sub * sub;
    else return x * sub * sub;
}

template<typename Predicate, typename Acc>
constexpr Acc keep_best(Predicate, Acc x) {
    return x;
}

template<typename Predicate, typename Acc, typename... Rest>
constexpr Acc keep_best(Predicate is_best, Acc x, Acc y, Rest... args) {
    return keep_best(is_best, (is_best(y, x) ? y : x), args...);
}

template<typename Head, typename... Rest>
constexpr Head min(Head x, Rest... args) {
    return keep_best(std::less<Head>(), x, args...);
}

template<typename Head, typename... Rest>
constexpr Head max(Head x, Rest... args) {
    return keep_best(std::greater<Head>(), x, args...);
}

} // namespace detai
} // namespace inom
