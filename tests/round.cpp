#include <cstdio>
#include <pfs/math/round.hpp>
#include "catch.hpp"

TEST_CASE("Check round()", "[math/round]") {

    REQUIRE(pfs::round(static_cast<float>(0.f)) == 0.f);
    REQUIRE(pfs::round(static_cast<double>(0.f)) == 0.f);
    REQUIRE(pfs::round(static_cast<long double>(0.0f)) == 0.f);

    REQUIRE(pfs::round(static_cast<float>(-0.f)) == -0.f);
    REQUIRE(pfs::round(static_cast<double>(-0.f)) == -0.f);
    REQUIRE(pfs::round(static_cast<long double>(-0.0f)) == -0.f);

    REQUIRE(pfs::round(static_cast<float>(2.3f)) == 2.f);
    REQUIRE(pfs::round(static_cast<double>(2.3f)) == 2.f);
    REQUIRE(pfs::round(static_cast<long double>(2.3f)) == 2.f);

    REQUIRE(pfs::round(static_cast<float>(2.5f)) == 3.f);
    REQUIRE(pfs::round(static_cast<double>(2.5f)) == 3.f);
    REQUIRE(pfs::round(static_cast<long double>(2.5f)) == 3.f);

    REQUIRE(pfs::round(static_cast<float>(2.7f)) == 3.f);
    REQUIRE(pfs::round(static_cast<double>(2.7f)) == 3.f);
    REQUIRE(pfs::round(static_cast<long double>(2.7f)) == 3.f);

    REQUIRE(pfs::round(static_cast<float>(-2.3f)) == -2.f);
    REQUIRE(pfs::round(static_cast<double>(-2.3f)) == -2.f);
    REQUIRE(pfs::round(static_cast<long double>(-2.3f)) == -2.f);

    REQUIRE(pfs::round(static_cast<float>(-2.5f)) == -3.f);
    REQUIRE(pfs::round(static_cast<double>(-2.5f)) == -3.f);
    REQUIRE(pfs::round(static_cast<long double>(-2.5f)) == -3.f);

    REQUIRE(pfs::round(static_cast<float>(-2.7f)) == -3.f);
    REQUIRE(pfs::round(static_cast<double>(-2.7f)) == -3.f);
    REQUIRE(pfs::round(static_cast<long double>(-2.7f)) == -3.f);

    REQUIRE(pfs::round(static_cast<float>(2.5f)) == 3.f);
    REQUIRE(pfs::round(static_cast<float>(0.25f) * 10) == 3.f);   // Ok
    REQUIRE(pfs::round(static_cast<float>(0.35f) * 10) == 4.f);   // Ok
    REQUIRE(pfs::round(static_cast<double>(0.25f) * 10) == 3.f);  // Ok
    REQUIRE(pfs::round(static_cast<double>(3.5f)) == 4.f);        // Ok

    printf("%e; %e" , static_cast<double>(0.35f), 10 * static_cast<double>(0.35f));

    // FIXME
    //REQUIRE(pfs::round(static_cast<double>(0.35f) 10) == 4.f);  // Failed
}
