#pragma once

#include <type_traits>
#include "integer.hpp"

namespace inom {

// checks if a value is included in the range
template<class Range, range_t I>
struct includes {
    static constexpr bool value = (I >= Range::lbound && I <= Range::rbound);
};

// checks if the range includes any positive value
template<class Range>
struct includes_positives {
    static constexpr bool value = (Range::rbound > 0);
};

// checks if the range includes any negative value
template<class Range>
struct includes_negatives {
    static constexpr bool value = (Range::lbound < 0);
};

// checks if a range contains only a single value
template<class Range>
struct is_singleton {
    static constexpr bool value = (Range::lbound == Range::rbound);
};

} // namespace inom
