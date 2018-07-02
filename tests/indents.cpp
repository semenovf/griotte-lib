#include "catch.hpp"
#include <pfs/griotte/indents.hpp>

SCENARIO("Indents constructors", "[indents]") {
    using indents = pfs::griotte::indents;

    GIVEN("A indents") {
        WHEN("created with default constructor") {
            indents x;

            THEN("all attributes are zero") {
                REQUIRE(x.top() == 0);
                REQUIRE(x.right() == 0);
                REQUIRE(x.bottom() == 0);
                REQUIRE(x.left() == 0);
            }
        }

        AND_WHEN("created by default copy constructor") {
            indents x;
            indents y(x);

            THEN("all attributes are zero") {
                REQUIRE(y.top() == 0);
                REQUIRE(y.right() == 0);
                REQUIRE(y.bottom() == 0);
                REQUIRE(y.left() == 0);
            }
        }

        AND_WHEN("assigned by default copy assignment operator") {
            indents x;
            indents y;
            y = x;

            THEN("all attributes are zero") {
                REQUIRE(y.top() == 0);
                REQUIRE(y.right() == 0);
                REQUIRE(y.bottom() == 0);
                REQUIRE(y.left() == 0);
            }
        }
    }
}
