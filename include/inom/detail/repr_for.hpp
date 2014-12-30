#pragma once

#include <cstdint>
#include <type_traits>
#include "../aliases.hpp"

namespace inom {
namespace detail {

template<intdata_t N, typename _ = void>
struct repr_for {
    using type = std::uint8_t;
};

template<intdata_t N>
struct repr_for<
    N, 
    typename std::enable_if<(N > UINT8_MAX && N < UINT16_MAX)>::type
> {
    using type = std::uint16_t;
};

template<intdata_t N>
struct repr_for<
    N, 
    typename std::enable_if<(N > UINT16_MAX && N < UINT32_MAX)>::type
> {
    using type = std::uint32_t;
};


template<intdata_t N>
struct repr_for<
    N, 
    typename std::enable_if<(N > UINT32_MAX)>::type
> {
    using type = std::uint64_t;
};

} // namespace detail
} // namespace inom
