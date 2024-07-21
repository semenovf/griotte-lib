////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.21 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "item.hpp"
#include <pfs/filesystem.hpp>
#include <memory>

namespace griotte {

class image: public item
{
    class impl;

private:
    std::unique_ptr<impl> _pimpl;

public:
    image ();
    ~image ();

    bool load (pfs::filesystem::path const & image_path);

    void render (renderer_ptr_t r) override;
};

} // namespace griotte


