#include "../../ext/catch.hpp"
#include "../../include/inom/type_traits.hpp"

TEST_CASE("inom::includes") {

    SECTION("it returns true if the specified element is in the range") {
        REQUIRE((inom::includes<inom::integer<0, 23>, 0>::value) == true);
        REQUIRE((inom::includes<inom::integer<0, 23>, -1>::value) == false);
        REQUIRE((inom::includes<inom::integer<-6, 23>, -2>::value) == true);
        REQUIRE((inom::includes<inom::integer<-39, -2>, 0>::value) == false);
    }

}

TEST_CASE("inom::includes_positives") {

    SECTION("it returns true if the range includes positive numbers") {
        REQUIRE((inom::includes_positives<inom::integer<0, 23>>::value) == true);
        REQUIRE((inom::includes_positives<inom::integer<-30, 0>>::value) == false);
        REQUIRE((inom::includes_positives<inom::integer<-6, 23>>::value) == true);
        REQUIRE((inom::includes_positives<inom::integer<-39, -2>>::value) == false);
    }

}

TEST_CASE("inom::includes_negatives") {

    SECTION("it returns true if the range includes negative numners") {
        REQUIRE((inom::includes_negatives<inom::integer<0, 23>>::value) == false);
        REQUIRE((inom::includes_negatives<inom::integer<-32, 0>>::value) == true);
        REQUIRE((inom::includes_negatives<inom::integer<-6, 23>>::value) == true);
        REQUIRE((inom::includes_negatives<inom::integer<3, 38>>::value) == false);
    }

}

TEST_CASE("inom::is_singleton") {

    SECTION("it returns true if the range includes negative numbers") {
        REQUIRE((inom::is_singleton<inom::integer<0, 23>>::value) == false);
        REQUIRE((inom::is_singleton<inom::integer<0, 0>>::value) == true);
        REQUIRE((inom::is_singleton<inom::integer<-6, -6>>::value) == true);
        REQUIRE((inom::is_singleton<inom::integer<4, 4>>::value) == true);
    }

}
