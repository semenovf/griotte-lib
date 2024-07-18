////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.13 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "casting.hpp"
#include "log_guard.hpp"
#include "griotte/SFML/ui.hpp"
#include "griotte/fixed_layout.hpp"
#include "griotte/logger.hpp"
#include <pfs/i18n.hpp>
#include <pfs/log.hpp>
#include <pfs/memory.hpp>
#include <pfs/stopwatch.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <sstream>
#include <thread>

namespace griotte {
namespace SFML {

ui::ui (options && opts)
{
    // Same as sf::Style::Default
    sf::Uint32 style = sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close;

    sf::ContextSettings settings;
    settings.depthBits = opts.depth_bits;
    settings.stencilBits = 8;
    settings.antialiasingLevel = opts.antialiasing_level;
    settings.majorVersion = 3;
    settings.minorVersion = 0;

    // Create window
    _win = pfs::make_unique<sf::RenderWindow>(sf::VideoMode(opts.w, opts.h)
        , sf::String::fromUtf8(opts.title.begin(), opts.title.end())
        , style, settings);

    // Activate vertical synchronization
    // NOTE. Never use both `setVerticalSyncEnabled` and `setFramerateLimit` at the same time!
    // They would badly mix and make things worse.
    _win->setVerticalSyncEnabled(true); // call it once, after creating the window
    //_win->setFramerateLimit(60);

    _win->setPosition(sf::Vector2i(opts.x, opts.y));

    sf::Vector2u size = _win->getSize();
    _win_w = size.x;
    _win_h = size.y;

    _root_layout = pfs::make_unique<fixed_layout>();
}

ui::~ui ()
{
    // Destroy window
    if (_win)
        _win.reset();
}

void ui::set_color (color_t value)
{
    _color = value;
}

void ui::step (sf::Event * ev)
{
    switch (ev->type) {
        case sf::Event::Closed:
            _running = false;
            break;

        case sf::Event::Resized: {
            _win_w = ev->size.width;
            _win_h = ev->size.height;

            // Update the view to the new size of the window
            sf::FloatRect visibleArea(0, 0, _win_w, _win_h);
            _win->setView(sf::View(visibleArea));

            //LOG_TRACE_1("sf::Event::Resized: {}x{}", _win_w, _win_h);
            _update_required = true;
            break;
        }

        // Window lost focus
        case sf::Event::LostFocus:
            break;

        // Window gained focus
        case sf::Event::GainedFocus:
            break;

        default:
            break;
    }
}

void ui::step ()
{
    sf::Event ev;

    while (_win->pollEvent(ev))
        step(& ev);

    if (_update_required) {
        sf::Vector2u size = _win->getSize();
        _root_layout->set_width(size.x);
        _root_layout->set_height(size.y);
        _root_layout->update();

        _win->clear(cast(_color));
        _root_layout->render(& *_win);

        _win->display();
        _update_required = false;
    }
}

void ui::run ()
{
    // TODO Must be initialized with analogue from SFML of SDL_DisplayMode.refresh_rate value
    // returned by SDL_GetDesktopDisplayMode()
    float millis_per_frame = 1000.0 / 60.0;

    pfs::stopwatch<std::milli, std::int32_t> stopwatch;

    while (_running) {
        stopwatch.start();
        step();
        stopwatch.stop();

        /* figure out how much time we have left, and then sleep */
        auto remain_millis = static_cast<std::int32_t>(millis_per_frame - stopwatch.count());

        if (remain_millis < 0) {
            remain_millis = 0;
        } else if (remain_millis > millis_per_frame) {
            remain_millis = millis_per_frame;
        }

        if (remain_millis > 0)
            std::this_thread::sleep_for(std::chrono::milliseconds{remain_millis});
    }
}

bool ui::load_font (std::string const & font_alias, pfs::filesystem::path const & path)
{
    auto font = pfs::make_unique<sf::Font>();
    log_guard lg;

    if (!font->loadFromFile(pfs::filesystem::utf8_encode(path))) {
        return false;
    }

    if (_fonts.find(font_alias) != _fonts.end()) {
        logger::e(tr::f_("font alias already occupied by font: {}, change font alias for file: {}"
            , font_alias, path));
        return false;
    }

    _fonts[font_alias] = std::move(font);

    return true;
}

}} // namespace griotte::SFML
