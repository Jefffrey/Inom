#include "../../ext/catch.hpp"
#include "../../include/inom/util.hpp"

TEST_CASE("inom::detail::constexpr_abs") {

    SECTION("it returns 0 on 0") {
        REQUIRE(inom::detail::constexpr_abs(0) == 0);
    }

    SECTION("it returns the absolute value") {
        REQUIRE(inom::detail::constexpr_abs(1) == 1);
        REQUIRE(inom::detail::constexpr_abs(2) == 2);
        REQUIRE(inom::detail::constexpr_abs(1024) == 1024);
        REQUIRE(inom::detail::constexpr_abs(-1) == 1);
        REQUIRE(inom::detail::constexpr_abs(-2) == 2);
        REQUIRE(inom::detail::constexpr_abs(-1024) == 1024);
    }

}
