////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.21 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "log_guard.hpp"
#include "griotte/image.hpp"
#include <pfs/memory.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace griotte {

class image::impl
{
public:
    sf::Image image;
    sf::Sprite sprite;
    sf::Texture texture;

public:
};

image::image (): item() {}
image::~image () = default;

bool image::load (pfs::filesystem::path const & image_path)
{
    SFML::log_guard lg;

    auto pimpl = pfs::make_unique<impl>();
    auto success = pimpl->image.loadFromFile(pfs::filesystem::utf8_encode(image_path));

    if (!success)
        return false;

    success = pimpl->texture.loadFromImage(pimpl->image);

    if (!success)
        return false;

    pimpl->sprite.setTexture(pimpl->texture, true);

    _pimpl = std::move(pimpl);

    return true;
}

template <>
void render<image, sf::RenderTarget> (image & item, sf::RenderTarget & r)
{
    item.render(& r);
}

void image::render (sf::RenderTarget * r)
{
    if (_pimpl == nullptr)
        return;

    _pimpl->sprite.setPosition(x(), y());

    r->draw(_pimpl->sprite);
}

} // namespace griotte
