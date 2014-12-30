#pragma once

#include <cinttypes>

namespace inom {
namespace detail {

constexpr std::intmax_t abs(std::intmax_t n) {
    return (n >= 0) ? n : -n; 
}

} // namespace detai
} // namespace inom
