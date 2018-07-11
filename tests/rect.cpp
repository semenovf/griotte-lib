#include "catch.hpp"

#define PFS_GRIOTTE_SOURCE
#include <pfs/griotte/rect.hpp>

using rect = pfs::griotte::rect;

SCENARIO("Rect constructors", "[rect]") {
    GIVEN("A rect") {
        WHEN("created with default constructor") {
            rect r;

            THEN("all attributes are zero") {
                REQUIRE(r.x() == 0);
                REQUIRE(r.y() == 0);
                REQUIRE(r.width() == 0);
                REQUIRE(r.height() == 0);
            }
        }

        AND_WHEN("created by default copy constructor") {
            rect r1;
            rect r2(r1);

            THEN("all attributes are zero") {
                REQUIRE(r2.x() == 0);
                REQUIRE(r2.y() == 0);
                REQUIRE(r2.width() == 0);
                REQUIRE(r2.height() == 0);
            }
        }

        AND_WHEN("assigned by default copy assignment operator") {
            rect r1;
            rect r2;
            r2 = r1;

            THEN("all attributes are zero") {
                REQUIRE(r2.x() == 0);
                REQUIRE(r2.y() == 0);
                REQUIRE(r2.width() == 0);
                REQUIRE(r2.height() == 0);
            }
        }
    }
}

TEST_CASE("Rect contains point including edges", "[rect]") {
    rect r(10, 20, 30, 40);

    REQUIRE(r.contains(10, 20) == true);  // point on bottom-left corner
    REQUIRE(r.contains(39, 59) == true);  // point on top-right corner
    REQUIRE(r.contains(39, 20) == true);  // point on bottom-right corner
    REQUIRE(r.contains(10, 59) == true);  // point on top-left corner
    REQUIRE(r.contains(25, 20) == true);  // point on bottom edge
    REQUIRE(r.contains(39, 40) == true);  // point on right edge
    REQUIRE(r.contains(25, 59) == true);  // point on top edge
    REQUIRE(r.contains(10, 40) == true);  // point on left edge
    REQUIRE(r.contains(25, 40) == true);  // point on near the rect center
    REQUIRE(r.contains(25, 19) == false); // point below the rect
    REQUIRE(r.contains(40, 40) == false); // point to the right of the rect
    REQUIRE(r.contains(25, 60) == false); // point higher the rect
    REQUIRE(r.contains(9 , 40) == false); // point to the left of the rect
}

TEST_CASE("Rect contains point excluding edges", "[rect]") {
    rect r(10, 20, 30, 40);

    REQUIRE(r.contains_exclude_edge(10, 20) == false); // point on bottom-left corner
    REQUIRE(r.contains_exclude_edge(39, 59) == false); // point on top-right corner
    REQUIRE(r.contains_exclude_edge(39, 20) == false); // point on bottom-right corner
    REQUIRE(r.contains_exclude_edge(10, 59) == false); // point on top-left corner
    REQUIRE(r.contains_exclude_edge(25, 20) == false); // point on bottom edge
    REQUIRE(r.contains_exclude_edge(39, 40) == false); // point on right edge
    REQUIRE(r.contains_exclude_edge(25, 59) == false); // point on top edge
    REQUIRE(r.contains_exclude_edge(10, 40) == false); // point on left edge
    REQUIRE(r.contains_exclude_edge(25, 40) == true);  // point on near the rect center
    REQUIRE(r.contains_exclude_edge(25, 19) == false); // point below the rect
    REQUIRE(r.contains_exclude_edge(40, 40) == false); // point to the right of the rect
    REQUIRE(r.contains_exclude_edge(25, 60) == false); // point higher the rect
    REQUIRE(r.contains_exclude_edge(9 , 40) == false); // point to the left of the rect
}
