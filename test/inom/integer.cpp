#include "../../ext/catch.hpp"
#include "../../include/inom/integer.hpp"
#include <type_traits>

TEST_CASE("inom::make_int") {

    SECTION("it creates integers") {
        inom::integer<123, 123> x = inom::make_int<123>();
        REQUIRE(x.data() == 123);
    }

}

TEST_CASE("inom::integer") {

    SECTION("access to the underlying data") {
        inom::integer<-3, 5> x = inom::make_int<2>();
        inom::integer<0, 0> y = inom::make_int<0>();
        inom::integer<4, 9> z = inom::make_int<7>();
        REQUIRE(x.data() == 2);
        REQUIRE(y.data() == 0);
        REQUIRE(z.data() == 7);
    }

    SECTION("can be default constructed") {
        inom::integer<123, 123> x;
        inom::integer<0, 123> y;
        inom::integer<-3, 8> z;
        REQUIRE(x.data() == 0);
        REQUIRE(y.data() == 0);
        REQUIRE(z.data() == 0);
    }

    SECTION("equality works") {
        auto x = inom::make_int<345>();
        auto y = x;
        auto z = inom::make_int<300>();
        inom::integer<123, 1002> w = z;
        inom::integer<-1, 4> p = inom::make_int<-1>();
        inom::integer<45, 301> q = inom::make_int<300>();
        inom::integer<280, 1200> r = inom::make_int<300>();

        REQUIRE(x == y);
        REQUIRE((x != y) == false);
        REQUIRE(x != z);
        REQUIRE((x == z) == false);
        REQUIRE(z == w);
        REQUIRE((z != w) == false);
        REQUIRE(p != w);
        REQUIRE((p == w) == false);
        REQUIRE(p == w);
        REQUIRE((p != w) == false);
        REQUIRE(p == r);
        REQUIRE((p != r) == false);
        REQUIRE(r == w);
        REQUIRE((r != w) == false);
    }

    SECTION("can be created from a more strict integer") {
        inom::integer<0, 11> x = inom::make_int<5>();
        inom::integer<0, 23> y = x;
        REQUIRE(x == y);
    }



}
