////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2025 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2025.08.21 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "griotte/label.hpp"

namespace griotte {

label_t::label_t ()
    : text_t ()
{}

label_t::label_t (std::string content)
    : text_t(std::move(content))
{}

label_t::~label_t () = default;

void label_t::clear_background_item ()
{
    auto node = first_child();

    if (node != nullptr) {
        auto * ptr = static_cast<item *>(node);
        delete ptr;
    }
}

void label_t::render (sf::RenderTarget * r)
{
    auto node = first_child();

    // Draw background
    if (node != nullptr)
        static_cast<item *>(node)->render(r);

    text_t::render(r);
}

} // namespace griotte::SFML
