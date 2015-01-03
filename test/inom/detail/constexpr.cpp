#include "../../../ext/catch.hpp"
#include "../../../include/inom/detail/constexpr.hpp"

using inom::detail::abs;
using inom::detail::min;
using inom::detail::max;
using inom::detail::power;

TEST_CASE("inom::detail::abs") {

    SECTION("it returns 0 on 0") {
        REQUIRE(abs(0) == 0);
    }

    SECTION("it returns the absolute value") {
        REQUIRE(abs(1) == 1);
        REQUIRE(abs(2) == 2);
        REQUIRE(abs(1024) == 1024);
        REQUIRE(abs(-1) == 1);
        REQUIRE(abs(-2) == 2);
        REQUIRE(abs(-1024) == 1024);
    }

}

TEST_CASE("inom::detail::min") {

    SECTION("it works for 1 element") {
        auto x = min(2);
        auto y = min(0);
        auto z = min(-2);
        REQUIRE(x == 2);
        REQUIRE(y == 0);
        REQUIRE(z == -2);
    }

    SECTION("it works for more elements") {
        auto x = min(3, -3, 5, 199, -459);
        auto y = min(3, -3, 5, 199, -459, 0);
        REQUIRE(x == -459);
        REQUIRE(y == -459);
    }

}

TEST_CASE("inom::detail::max") {

    SECTION("it works for 1 element") {
        auto x = max(2);
        auto y = max(0);
        auto z = max(-2);
        REQUIRE(x == 2);
        REQUIRE(y == 0);
        REQUIRE(z == -2);
    }

    SECTION("it works for more elements") {
        auto x = max(3, -3, 5, 199, -459);
        auto y = max(3, -3, 5, 199, -459, 0);
        REQUIRE(x == 199);
        REQUIRE(y == 199);
    }

}

TEST_CASE("inom::detail::power") {

    SECTION("it works to the power of 0") {
        auto x = power(3, 0);
        auto y = power(-4, 0);
        REQUIRE(x == 1);
        REQUIRE(y == 1);
    }

    SECTION("it works to the power of 1") {
        auto x = power(3, 1);
        auto y = power(-4, 1);
        REQUIRE(x == 3);
        REQUIRE(y == -4);
    }

    SECTION("it works for non trivial powers") {
        auto x = power(3, 4);
        auto y = power(-2, 9);
        auto z = power(5LL, 14);
        auto w = power(265LL, 4);
        REQUIRE(x == 81);
        REQUIRE(y == -512);
        REQUIRE(z == 6.103515625e9);
        REQUIRE(w == 4.931550625e9);
    }

}
