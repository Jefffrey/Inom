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

    SECTION("can be instantiated with a literal") {
        using namespace inom::literals;
        auto x = 123_int;
        auto y = 123_int;
        static_assert(
            std::is_same<decltype(x), decltype(y)>::value,
            "literal type mismatch"
        );
        static_assert(
            std::is_same<decltype(x), inom::i<123>>::value,
            "literal type mismatch"
        );
        REQUIRE(x == y);
        REQUIRE(x.data() == 123);
    }

    SECTION("can be instantiated with an hex literal") {
        using namespace inom::literals;
        auto x = 0x0_int;
        auto y = 0xb_int;
        auto z = 0x347ab3f893f_int;
        static_assert(
            std::is_same<decltype(x), inom::i<0>>::value,
            "hex literal type mismatch"
        );
        static_assert(
            std::is_same<decltype(y), inom::i<11>>::value,
            "hex literal type mismatch"
        );
        static_assert(
            std::is_same<decltype(z), inom::i<3606350629183>>::value,
            "hex literal type mismatch"
        );
        REQUIRE(0xb_int == 11_int);
        REQUIRE(x.data() == 0);
        REQUIRE(y.data() == 11);
        REQUIRE(z.data() == 3606350629183);
    }

    SECTION("can be instantiated with a binary literal") {
        using namespace inom::literals;
        auto x = 0b0001_int;
        auto y = 0b01_int;
        auto z = 0b011010110001_int;
        auto w = 0b0_int;
        static_assert(
            std::is_same<decltype(x), inom::i<1>>::value,
            "hex literal type mismatch"
        );
        static_assert(
            std::is_same<decltype(y), inom::i<1>>::value,
            "hex literal type mismatch"
        );
        static_assert(
            std::is_same<decltype(z), inom::i<1713>>::value,
            "hex literal type mismatch"
        );
        static_assert(
            std::is_same<decltype(w), inom::i<0>>::value,
            "hex literal type mismatch"
        );
        REQUIRE(x.data() == 1);
        REQUIRE(y == x);
        REQUIRE(z.data() == 1713);
        REQUIRE(w.data() == 0);
    }

    SECTION("can be instantiated with an octal literal") {
        using namespace inom::literals;
        auto x = 0001_int;
        auto y = 00001_int;
        auto z = 005702753_int;
        auto w = 00_int;

        static_assert(
            std::is_same<decltype(x), inom::i<1>>::value,
            "octal literal type mismatch"
        );
        static_assert(
            std::is_same<decltype(y), inom::i<1>>::value,
            "octal literal type mismatch"
        );
        static_assert(
            std::is_same<decltype(z), inom::i<1541611>>::value,
            "octal literal type mismatch"
        );
        static_assert(
            std::is_same<decltype(w), inom::i<0>>::value,
            "octal literal type mismatch"
        );
        REQUIRE(x.data() == 1);
        REQUIRE(y == x);
        REQUIRE(z.data() == 1541611);
        REQUIRE(w.data() == 0);
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

    SECTION("comparison works") {
        using namespace inom::literals;
        inom::integer<-34, 298> a = -33_int;
        inom::integer<300, 2698> b = 323_int;
        inom::integer<234, 400> c = 323_int;
        REQUIRE(a < b);
        REQUIRE(b > a);
        REQUIRE(b <= c);
        REQUIRE(b >= c);
        REQUIRE(c <= b);
        REQUIRE(c >= b);
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

    SECTION("multiplication works") {
        using namespace inom::literals;
        inom::i<3, 4> x = 4_int;
        inom::i<-4, 9> y = -3_int;
        auto z = 0_int;
        auto a = x * y;
        auto b = x * z;
        auto c = y * x;

        static_assert(
            std::is_same<decltype(a), inom::i<-16, 36>>::value,
            "multiplication type mismatch"
        );
        static_assert(
            std::is_same<decltype(b), inom::i<0, 0>>::value,
            "multiplication type mismatch"
        );
        static_assert(
            std::is_same<decltype(c), decltype(a)>::value,
            "multiplication type mismatch"
        );
        REQUIRE(a == -12_int);
        REQUIRE(a == c);
        REQUIRE(b == 0_int);
    }

    SECTION("can be created from a more strict integer") {
        using namespace inom::literals;
        inom::integer<0, 11> x = 5_int;
        inom::integer<0, 23> y = x;
        REQUIRE(x == y);
    }

}
