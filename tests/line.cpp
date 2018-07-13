#include "catch.hpp"

#define PFS_GRIOTTE_SOURCE
#include <pfs/griotte/line.hpp>

using line = pfs::griotte::line<int>;

SCENARIO("Rect constructors", "[line]") {
    GIVEN("A rect") {
        WHEN("created with default constructor") {
            line l;

            THEN("all attributes are zero") {
                REQUIRE(l.p1().x() == 0);
                REQUIRE(l.p1().y() == 0);
                REQUIRE(l.p2().x() == 0);
                REQUIRE(l.p2().y() == 0);
            }
        }

        AND_WHEN("created by default copy constructor") {
            line l1;
            line l2(l1);

            THEN("all attributes are zero") {
                REQUIRE(l2.p1().x() == 0);
                REQUIRE(l2.p1().y() == 0);
                REQUIRE(l2.p2().x() == 0);
                REQUIRE(l2.p2().y() == 0);
            }
        }

        AND_WHEN("assigned by default copy assignment operator") {
            line l1;
            line l2;
            l2 = l1;

            THEN("all attributes are zero") {
                REQUIRE(l2.p1().x() == 0);
                REQUIRE(l2.p1().y() == 0);
                REQUIRE(l2.p2().x() == 0);
                REQUIRE(l2.p2().y() == 0);
            }
        }
    }
}

