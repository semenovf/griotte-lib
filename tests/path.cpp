#include "catch.hpp"

#define PFS_GRIOTTE_SOURCE
#include <pfs/griotte/path.hpp>

using path = pfs::griotte::path<int>;
using point = pfs::griotte::point<int>;

SCENARIO("Path constructors", "[path]") {
    GIVEN("A path") {
        WHEN("created with default constructor") {
            path p;

            THEN("") {}
        }

        AND_WHEN("created by default copy constructor") {
            path p1;
            path p2{p1};

            THEN("") {}
        }

        AND_WHEN("assigned by default copy assignment operator") {
            path p1;
            path p2;
            p2 = p1;

            THEN("") {}
        }
    }

    GIVEN("A path") {
        WHEN("created with [path (point const & start)] constructor") {
            path p{point{10, 20}};

            THEN("") {}
        }

        AND_WHEN("created by copy constructor") {
            path p1{point{10, 20}};
            path p2{p1};

            THEN("") {}
        }

        AND_WHEN("assigned by copy assignment operator") {
            path p1{point{10, 20}};
            path p2;
            p2 = p1;

            THEN("") {}
        }
    }
}

// TEST_CASE("Set x and y coordinates", "[point]") {
//     point p;
//
//     p.set_x(10);
//     p.set_y(20);
//
//     REQUIRE(p.x() == 10);
//     REQUIRE(p.y() == 20);
// }
