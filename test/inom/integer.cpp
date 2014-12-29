#include "../../ext/catch.hpp"
#include "../../include/inom/integer.hpp"
#include <type_traits>

TEST_CASE("inom::make_int") {

    SECTION("it creates integers") {
        inom::integer<123, 123> x = inom::make_int<123>();
    }

}

TEST_CASE("inom::integer") {

    SECTION("can be default constructed") {
        inom::integer<123, 123> x;
        inom::integer<0, 123> y;
        inom::integer<-3, 8> z;
    }

    SECTION("can be created from an equally ranged integer") {
        inom::integer<123> x = inom::make_int<123>();
        inom::integer<123, 123> y = inom::make_int<123>();
    }

    SECTION("can be created from a more strict integer") {
        inom::integer<0, 11> x = inom::make_int<5>();
        inom::integer<0, 23> y = x;
    }

}
