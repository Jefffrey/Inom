#include "../../ext/catch.hpp"
#include "../../include/inom/integer.hpp"
#include <type_traits>
#include <cstdint>

TEST_CASE("inom::make_int") {

    SECTION("it creates integers") {
        inom::integer<123, 123> x = inom::make_int<123>();
        REQUIRE(x.data() == 123);
    }

}

TEST_CASE("inom::integer") {

    SECTION("can be default constructed") {
        inom::integer<-4, 0> x;
        inom::integer<0, 123> y;
        inom::integer<-3, 8> z;
        REQUIRE(x.data() == 0);
        REQUIRE(y.data() == 0);
        REQUIRE(z.data() == 0);
    }

    SECTION("can be instantiated as a literal") {
        using namespace inom::literals;
        auto x = 123_int;
        auto y = 123_int;
        REQUIRE(x == y);
        REQUIRE(x.data() == 123);
    }

    SECTION("access to the underlying data") {
        using namespace inom::literals;
        inom::integer<-3, 5> x = 2_int;
        inom::integer<0, 0> y = 0_int;
        inom::integer<4, 9> z = 7_int;
        REQUIRE(x.data() == 2);
        REQUIRE(y.data() == 0);
        REQUIRE(z.data() == 7);
    }

    SECTION("equality works") {
        using namespace inom::literals;
        auto x = 345_int;
        auto y = x;
        auto z = 300_int;
        inom::integer<123, 1002> w = z;
        inom::integer<-1, 4> p = -1_int;
        inom::integer<45, 301> q = 300_int;
        inom::integer<280, 1200> r = 300_int;

        REQUIRE(x == y);
        REQUIRE((x != y) == false);
        REQUIRE(x != z);
        REQUIRE((x == z) == false);
        REQUIRE(z == w);
        REQUIRE((z != w) == false);
        REQUIRE(p != w);
        REQUIRE((p == w) == false);
        REQUIRE(z == w);
        REQUIRE((z != w) == false);
        REQUIRE(z == r);
        REQUIRE((z != r) == false);
        REQUIRE(r == w);
        REQUIRE((r != w) == false);
    }

    SECTION("addition works") {
        using namespace inom::literals;
        inom::integer<-3, -1> x = -1_int;
        inom::integer<-6, 19> y = 6_int;
        auto z = x + y;

        static_assert(
            std::is_same<
                decltype(z),
                inom::integer<-9, 18>
            >::value,
            "addition type mismatch"
        );
        REQUIRE(z.data() == 5);
    }

    SECTION("subtraction works") {
        using namespace inom::literals;
        inom::integer<-3, -1> x = -1_int;
        inom::integer<-6, 19> y = 6_int;
        auto z = x - y;

        static_assert(
            std::is_same<
                decltype(z),
                inom::integer<-22, 5>
            >::value,
            "subtraction type mismatch"
        );
        REQUIRE(z.data() == -7);
    }

    SECTION("can be created from a more strict integer") {
        using namespace inom::literals;
        inom::integer<0, 11> x = 5_int;
        inom::integer<0, 23> y = x;
        REQUIRE(x == y);
    }

}
