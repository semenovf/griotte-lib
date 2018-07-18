#include "catch.hpp"

#include <utility>

#define PFS_GRIOTTE_SOURCE
#include <pfs/griotte/point.hpp>

using point = pfs::griotte::point<int>;

SCENARIO("Point constructors", "[point]") {
    GIVEN("A point") {
        WHEN("created with default constructor") {
            point p;

            THEN("all attributes are zero") {
                REQUIRE(p.get_x() == 0);
                REQUIRE(p.get_y() == 0);
            }
        }

        AND_WHEN("created by default copy constructor") {
            point p1;
            point p2{p1};

            THEN("all attributes are zero") {
                REQUIRE(p2.get_x() == 0);
                REQUIRE(p2.get_y() == 0);
            }
        }

        AND_WHEN("assigned by default copy assignment operator") {
            point p1;
            point p2;
            p2 = p1;

            THEN("all attributes are zero") {
                REQUIRE(p2.get_x() == 0);
                REQUIRE(p2.get_y() == 0);
            }
        }
    }

    GIVEN("A point") {
        WHEN("created with [point (unit_t x, unit_t y)] constructor") {
            point p{10, 20};

            THEN("attributes are set properly") {
                REQUIRE(p.get_x() == 10);
                REQUIRE(p.get_y() == 20);
            }
        }

        AND_WHEN("created by copy constructor") {
            point p1{10, 20};
            point p2{p1};

            THEN("attributes are set properly") {
                REQUIRE(p2.get_x() == 10);
                REQUIRE(p2.get_y() == 20);
            }
        }

        AND_WHEN("assigned by copy assignment operator") {
            point p1{10, 20};
            point p2;
            p2 = p1;

            THEN("attributes are set properly") {
                REQUIRE(p2.get_x() == 10);
                REQUIRE(p2.get_y() == 20);
            }
        }
    }
}

TEST_CASE("Set x and y coordinates", "[point]") {
    point p;

    p.set_x(10);
    p.set_y(20);

    REQUIRE(p.get_x() == 10);
    REQUIRE(p.get_y() == 20);
}

TEST_CASE("Increment x and y coordinates", "[point]") {
    point p{10, 20};

    p.increment_x(10);
    p.increment_y(20);

    REQUIRE(p.get_x() == 20);
    REQUIRE(p.get_y() == 40);

    p.increment_x(-10);
    p.increment_y(-20);

    REQUIRE(p.get_x() == 10);
    REQUIRE(p.get_y() == 20);

    p.increment(10, 20);

    REQUIRE(p.get_x() == 20);
    REQUIRE(p.get_y() == 40);

    p.increment(-10, -20);

    REQUIRE(p.get_x() == 10);
    REQUIRE(p.get_y() == 20);
}

TEST_CASE("Adds and substructs operations", "[point]") {
    point p{10, 20};
    point p1{10, 20};
    point p2{-10, -20};

    p += p1;

    REQUIRE(p.get_x() == 20);
    REQUIRE(p.get_y() == 40);

    p += p2;

    REQUIRE(p.get_x() == 10);
    REQUIRE(p.get_y() == 20);

    p -= p2;

    REQUIRE(p.get_x() == 20);
    REQUIRE(p.get_y() == 40);

    p -= p1;

    REQUIRE(p.get_x() == 10);
    REQUIRE(p.get_y() == 20);
}

TEST_CASE("Multiplies by the given factor", "[point]") {
    point p;

    p = point{10, 10};
    p *= static_cast<float>(0.35);

    REQUIRE(p.get_x() == 4);
    REQUIRE(p.get_y() == 4);

    p = point{10, 10};
    p *= static_cast<float>(0.33);

    REQUIRE(p.get_x() == 3);
    REQUIRE(p.get_y() == 3);

    p = point{10, 10};
    p *= static_cast<float>(0.55);

    REQUIRE(p.get_x() == 6);
    REQUIRE(p.get_y() == 6);

    p = point{10, 10};
    p *= static_cast<float>(-0.35);

    REQUIRE(p.get_x() == -4);
    REQUIRE(p.get_y() == -4);

    p = point{10, 10};
    p *= static_cast<float>(-0.33);

    REQUIRE(p.get_x() == -3);
    REQUIRE(p.get_y() == -3);

    p = point{10, 10};
    p *= static_cast<float>(-0.55);

    REQUIRE(p.get_x() == -6);
    REQUIRE(p.get_y() == -6);

    p = point{10, 10};
    p *= static_cast<double>(0.35);

    REQUIRE(p.get_x() == 4);
    REQUIRE(p.get_y() == 4);

    p = point{10, 10};
    p *= static_cast<double>(0.33);

    REQUIRE(p.get_x() == 3);
    REQUIRE(p.get_y() == 3);

    p = point{10, 10};
    p *= static_cast<double>(0.55);

    REQUIRE(p.get_x() == 6);
    REQUIRE(p.get_y() == 6);

    p = point{10, 10};
    p *= static_cast<double>(-0.35);

    REQUIRE(p.get_x() == -4);
    REQUIRE(p.get_y() == -4);

    p = point{10, 10};
    p *= static_cast<double>(-0.33);

    REQUIRE(p.get_x() == -3);
    REQUIRE(p.get_y() == -3);

    p = point{10, 10};
    p *= static_cast<double>(-0.55);

    REQUIRE(p.get_x() == -6);
    REQUIRE(p.get_y() == -6);
}

TEST_CASE("Points comparison", "[point]") {
    REQUIRE(point{10, 10} == point{10, 10});
    REQUIRE(point{10, 10} != point{10, 11});
    REQUIRE(point{10, 10} != point{11, 11});
}
