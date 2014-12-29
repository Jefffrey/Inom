#pragma once

#include <cstdint>
#include <type_traits>

namespace inom {
namespace detail {

using max_n = std::int64_t;

constexpr max_n constexpr_abs(max_n i) {
    return (i < 0)
        ? -i
        : i;
}

template<max_n N, typename _ = void>
struct repr_for {
    using type = std::uint8_t;
};

template<max_n N>
struct repr_for<
    N, 
    typename std::enable_if<(N > UINT8_MAX && N < UINT16_MAX)>::type
> {
    using type = std::uint16_t;
};

template<max_n N>
struct repr_for<
    N, 
    typename std::enable_if<(N > UINT16_MAX && N < UINT32_MAX)>::type
> {
    using type = std::uint32_t;
};


template<max_n N>
struct repr_for<
    N, 
    typename std::enable_if<(N > UINT32_MAX)>::type
> {
    using type = std::uint64_t;
};

} // namespace detail
} // namespace inom
