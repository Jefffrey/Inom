#pragma once

#include <type_traits>
#include "aliases.hpp"
#include "integer.hpp"

namespace inom {

template<class Range, typename Range::data_t I>
struct includes {
    static constexpr bool value = (I >= Range::lbound && I <= Range::rbound);
};

template<class Range>
struct includes_positives {
    static constexpr bool value = (Range::rbound > 0);
};

template<class Range>
struct includes_negatives {
    static constexpr bool value = (Range::lbound < 0);
};

template<class Range>
struct is_singleton {
    static constexpr bool value = (Range::lbound == Range::rbound);
};

} // namespace inom
