////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.18 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "logger.hpp"
#include <SFML/System/Err.hpp>
#include <sstream>

namespace griotte {

inline std::ostringstream & log_stream ()
{
    static std::ostringstream oss;
    return oss;
}

class log_guard
{
    std::ostringstream & _oss;
    std::streambuf * _default_buf {nullptr};

public:
    log_guard () : _oss(log_stream())
    {
        _default_buf = sf::err().rdbuf();
        sf::err().rdbuf(_oss.rdbuf());
    }

    ~log_guard ()
    {
        auto text = _oss.str();
        _oss.clear();
        _oss.str(std::string{});

        sf::err().rdbuf(_default_buf);

        if (!text.empty())
            logger::e(text);
    }
};

} // namespace griotte::SFML

