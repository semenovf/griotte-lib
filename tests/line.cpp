#include "catch.hpp"

#define PFS_GRIOTTE_SOURCE
#include <pfs/griotte/line.hpp>

using line = pfs::griotte::line<int>;

SCENARIO("Rect constructors", "[line]") {
    GIVEN("A rect") {
        WHEN("created with default constructor") {
            line l;

            THEN("all attributes are zero") {
                REQUIRE(l.get_start_point().get_x() == 0);
                REQUIRE(l.get_start_point().get_y() == 0);
                REQUIRE(l.get_end_point().get_x() == 0);
                REQUIRE(l.get_end_point().get_y() == 0);
            }
        }

        AND_WHEN("created by default copy constructor") {
            line l1;
            line l2(l1);

            THEN("all attributes are zero") {
                REQUIRE(l2.get_start_point().get_x() == 0);
                REQUIRE(l2.get_start_point().get_y() == 0);
                REQUIRE(l2.get_end_point().get_x() == 0);
                REQUIRE(l2.get_end_point().get_y() == 0);
            }
        }

        AND_WHEN("assigned by default copy assignment operator") {
            line l1;
            line l2;
            l2 = l1;

            THEN("all attributes are zero") {
                REQUIRE(l2.get_start_point().get_x() == 0);
                REQUIRE(l2.get_start_point().get_y() == 0);
                REQUIRE(l2.get_end_point().get_x() == 0);
                REQUIRE(l2.get_end_point().get_y() == 0);
            }
        }
    }
}
