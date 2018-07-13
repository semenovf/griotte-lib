#include <cstdio>
#include <pfs/math/round.hpp>
#include "catch.hpp"

TEST_CASE("Check round()", "[math/round]") {

    REQUIRE(pfs::round(static_cast<float>(0.0)) == 0);
    REQUIRE(pfs::round(static_cast<double>(0.0)) == 0);
    REQUIRE(pfs::round(static_cast<long double>(0.0)) == 0);

    REQUIRE(pfs::round(static_cast<float>(-0.0)) == -0);
    REQUIRE(pfs::round(static_cast<double>(-0.0)) == -0);
    REQUIRE(pfs::round(static_cast<long double>(-0.0)) == -0);

    REQUIRE(pfs::round(static_cast<float>(2.3)) == 2);
    REQUIRE(pfs::round(static_cast<double>(2.3)) == 2);
    REQUIRE(pfs::round(static_cast<long double>(2.3)) == 2);

    REQUIRE(pfs::round(static_cast<float>(2.5)) == 3);
    REQUIRE(pfs::round(static_cast<double>(2.5)) == 3);
    REQUIRE(pfs::round(static_cast<long double>(2.5)) == 3);

    REQUIRE(pfs::round(static_cast<float>(2.7)) == 3.f);
    REQUIRE(pfs::round(static_cast<double>(2.7)) == 3.f);
    REQUIRE(pfs::round(static_cast<long double>(2.7)) == 3.f);

    REQUIRE(pfs::round(static_cast<float>(-2.3)) == -2.f);
    REQUIRE(pfs::round(static_cast<double>(-2.3)) == -2.f);
    REQUIRE(pfs::round(static_cast<long double>(-2.3)) == -2.f);

    REQUIRE(pfs::round(static_cast<float>(-2.5)) == -3.f);
    REQUIRE(pfs::round(static_cast<double>(-2.5)) == -3.f);
    REQUIRE(pfs::round(static_cast<long double>(-2.5)) == -3.f);

    REQUIRE(pfs::round(static_cast<float>(-2.7)) == -3.f);
    REQUIRE(pfs::round(static_cast<double>(-2.7)) == -3.f);
    REQUIRE(pfs::round(static_cast<long double>(-2.7)) == -3.f);

    REQUIRE(pfs::round(static_cast<float>(2.5)) == 3);
    REQUIRE(pfs::round(static_cast<float>(0.25) * 10) == 3);
    REQUIRE(pfs::round(static_cast<float>(0.35) * 10) == 4);
    REQUIRE(pfs::round(static_cast<double>(0.25) * 10) == 3);
    REQUIRE(pfs::round(static_cast<double>(3.5)) == 4);
    REQUIRE(pfs::round(static_cast<double>(0.35) * 10) == 4);

    REQUIRE(pfs::lround(static_cast<float>(0.0)) == 0L);
    REQUIRE(pfs::lround(static_cast<double>(0.0)) == 0L);
    REQUIRE(pfs::lround(static_cast<long double>(0.0)) == 0L);

    REQUIRE(pfs::lround(static_cast<float>(-0.0)) == -0L);
    REQUIRE(pfs::lround(static_cast<double>(-0.0)) == -0L);
    REQUIRE(pfs::lround(static_cast<long double>(-0.0)) == -0L);

    REQUIRE(pfs::lround(static_cast<float>(2.3)) == 2L);
    REQUIRE(pfs::lround(static_cast<double>(2.3)) == 2L);
    REQUIRE(pfs::lround(static_cast<long double>(2.3)) == 2L);

    REQUIRE(pfs::lround(static_cast<float>(2.5)) == 3L);
    REQUIRE(pfs::lround(static_cast<double>(2.5)) == 3L);
    REQUIRE(pfs::lround(static_cast<long double>(2.5)) == 3L);

    REQUIRE(pfs::lround(static_cast<float>(2.7)) == 3L);
    REQUIRE(pfs::lround(static_cast<double>(2.7)) == 3L);
    REQUIRE(pfs::lround(static_cast<long double>(2.7)) == 3L);

    REQUIRE(pfs::lround(static_cast<float>(-2.3)) == -2L);
    REQUIRE(pfs::lround(static_cast<double>(-2.3)) == -2L);
    REQUIRE(pfs::lround(static_cast<long double>(-2.3)) == -2L);

    REQUIRE(pfs::lround(static_cast<float>(-2.5)) == -3L);
    REQUIRE(pfs::lround(static_cast<double>(-2.5)) == -3L);
    REQUIRE(pfs::lround(static_cast<long double>(-2.5)) == -3L);

    REQUIRE(pfs::lround(static_cast<float>(-2.7)) == -3L);
    REQUIRE(pfs::lround(static_cast<double>(-2.7)) == -3L);
    REQUIRE(pfs::lround(static_cast<long double>(-2.7)) == -3L);

    REQUIRE(pfs::lround(static_cast<float>(2.5)) == 3L);
    REQUIRE(pfs::lround(static_cast<float>(0.25) * 10) == 3L);
    REQUIRE(pfs::lround(static_cast<float>(0.35) * 10) == 4L);
    REQUIRE(pfs::lround(static_cast<double>(0.25) * 10) == 3L);
    REQUIRE(pfs::lround(static_cast<double>(3.5)) == 4L);
    REQUIRE(pfs::lround(static_cast<double>(0.35) * 10) == 4L);
}
