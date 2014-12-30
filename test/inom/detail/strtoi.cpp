#include "../../../ext/catch.hpp"
#include "../../../include/inom/detail/strtoi.hpp"

TEST_CASE("inom::detail::strtoi") {

    SECTION("works with positive simple numbers") {
        REQUIRE((+inom::detail::strtoi<'0'>::value) == 0); 
        REQUIRE((+inom::detail::strtoi<'1', '2', '3'>::value) == 123); 
        REQUIRE((+inom::detail::strtoi<'8', '7'>::value) == 87); 
    }

    SECTION("works with leading 0 numbers") {
        REQUIRE((+inom::detail::strtoi<'0', '0'>::value) == 0); 
        REQUIRE((+inom::detail::strtoi<'0', '0', '0', '1', '2', '3'>::value) == 123); 
        REQUIRE((+inom::detail::strtoi<'0', '0', '8', '7'>::value) == 87); 
    }

}
