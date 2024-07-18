////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.15 Initial version.
////////////////////////////////////////////////////////////////////////////////
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <griotte/fixed_layout.hpp>
#include <griotte/button.hpp>

TEST_CASE("Basic") {
    griotte::fixed_layout layout1;

    // auto & button1 = layout1.create<griotte::button>();
    // auto & button2 = layout1.create<griotte::button>();
    // auto & button3 = layout1.create<griotte::button>();

    // using exit_status = modulus2_type::exit_status;
    // modulus2_type::dispatcher d{iostream_logger{}, null_settings{}};
    //
    // int timeout = 2; // seconds
    // timer_quit_plugin timer_quit_plugin {timeout};
    //
    // custom_module_lifetime_plugin lifetime_plugin;
    // d.attach_plugin(lifetime_plugin);
    //
    // CHECK(d.register_module<m1>(std::make_pair("m1", "")));
    // CHECK(d.register_module<m2>(std::make_pair("m2", ""), 42));
    // CHECK(d.register_module<m3>(std::make_pair("m3", ""), 43, "hello"));
    // CHECK(d.register_module<m4>(std::make_pair("m4", "m3")));
    // CHECK(d.register_module<m5>(std::make_pair("m5", "")));
    // CHECK(d.register_module<m6>(std::make_pair("m6", "m3")));
    //
    // CHECK(d.count() == 6);
    //
    // d.attach_plugin(timer_quit_plugin);
    // CHECK(d.exec() == exit_status::success);
    // CHECK_EQ(__timer_counter, 5);
}
