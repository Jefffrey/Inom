#include "../../../ext/catch.hpp"
#include "../../../include/inom/detail/constexpr.hpp"

TEST_CASE("inom::detail::abs") {

    SECTION("it returns 0 on 0") {
        REQUIRE(inom::detail::abs(0) == 0);
    }

    SECTION("it returns the absolute value") {
        REQUIRE(inom::detail::abs(1) == 1);
        REQUIRE(inom::detail::abs(2) == 2);
        REQUIRE(inom::detail::abs(1024) == 1024);
        REQUIRE(inom::detail::abs(-1) == 1);
        REQUIRE(inom::detail::abs(-2) == 2);
        REQUIRE(inom::detail::abs(-1024) == 1024);
    }

}
