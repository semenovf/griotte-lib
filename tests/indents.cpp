#include "catch.hpp"
#include <pfs/griotte/indents.hpp>

SCENARIO("Indents constructors", "[indents]") {
    using indents = pfs::griotte::indents<int>;

    GIVEN("A indents") {
        WHEN("created with default constructor") {
            indents x;

            THEN("all attributes are zero") {
                REQUIRE(x.get_top() == 0);
                REQUIRE(x.get_right() == 0);
                REQUIRE(x.get_bottom() == 0);
                REQUIRE(x.get_left() == 0);
            }
        }

        AND_WHEN("created by default copy constructor") {
            indents x;
            indents y(x);

            THEN("all attributes are zero") {
                REQUIRE(y.get_top() == 0);
                REQUIRE(y.get_right() == 0);
                REQUIRE(y.get_bottom() == 0);
                REQUIRE(y.get_left() == 0);
            }
        }

        AND_WHEN("assigned by default copy assignment operator") {
            indents x;
            indents y;
            y = x;

            THEN("all attributes are zero") {
                REQUIRE(y.get_top() == 0);
                REQUIRE(y.get_right() == 0);
                REQUIRE(y.get_bottom() == 0);
                REQUIRE(y.get_left() == 0);
            }
        }
    }
}
