////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.18 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "color.hpp"
#include "item.hpp"
#include <string>

namespace griotte {

class text: public item
{
protected:
    std::string _value;
    color_t _color;

public:
    text (): item () {}
    text (std::string value)
        : item ()
        , _value(std::move(value))
    {}

    ~text () = default;

    color_t color () const noexcept
    {
        return _color;
    }

    void set_color (color_t value)
    {
        _color = value;
    }

    std::string const & value () const noexcept
    {
        return _value;
    }

    void set_text (std::string value)
    {
        _value = std::move(value);
    }
};

} // namespace griotte

