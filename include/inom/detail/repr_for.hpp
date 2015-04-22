#pragma once

#include <cstdint>
#include <type_traits>

namespace inom {
namespace detail {

// type to infer the correct integer width
// based on the size of the integer
template<std::intmax_t N, typename _ = void>
struct repr_for {
    using type = std::uint8_t;
};

template<std::intmax_t N>
struct repr_for<
    N, 
    typename std::enable_if<(N > UINT8_MAX && N < UINT16_MAX)>::type
> {
    using type = std::uint16_t;
};

template<std::intmax_t N>
struct repr_for<
    N, 
    typename std::enable_if<(N > UINT16_MAX && N < UINT32_MAX)>::type
> {
    using type = std::uint32_t;
};


template<std::intmax_t N>
struct repr_for<
    N, 
    typename std::enable_if<(N > UINT32_MAX)>::type
> {
    using type = std::uint64_t;
};

} // namespace detail
} // namespace inom
