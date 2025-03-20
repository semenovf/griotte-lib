////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.13 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "casting.hpp"
#include "fixed_layout.hpp"
#include "font.hpp"
#include "SFML/ui.hpp"
#include <pfs/countdown_timer.hpp>
#include <pfs/i18n.hpp>
#include <pfs/memory.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <stdexcept>
#include <thread>
#include <type_traits>

#include <pfs/log.hpp>

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

    // FIXME What about Android?
    auto video_mode = sf::VideoMode::getDesktopMode();
    video_mode.width = opts.w;
    video_mode.height = opts.h;

    // Create window
    _win = pfs::make_unique<sf::RenderWindow>(video_mode
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

    // Load default (fallback font)
    if (!font::load()) {
        throw std::runtime_error(tr::_("loading default font failure"));
    }
}

ui::~ui ()
{
    // Destroy window
    if (_win)
        _win.reset();
}


unsigned int ui::width () const noexcept
{
    return _win_w;
}

unsigned int ui::height () const noexcept
{
    return _win_h;
}

void ui::set_color (color_t value)
{
    _color = value;
}

//
// NOTE Some code was partially borrowed from the project: "TGUI - Texus' Graphical User Interface"
// (https://github.com/texus/TGUI)
//
void ui::step (sf::Event * ev)
{
    // Detect scrolling with two fingers by examining touch events
    bool two_fingers_scrolling = (ev->type == sf::Event::TouchBegan)
        || (ev->type == sf::Event::TouchEnded)
        || (ev->type == sf::Event::TouchMoved);

    if (two_fingers_scrolling) {
        // FIXME
    //     const bool wasScrolling = m_twoFingerScroll.isScrolling();

        auto const finger_id = static_cast<std::intptr_t>(ev->touch.finger);
        float const x = static_cast<float>(ev->touch.x);
        float const y = static_cast<float>(ev->touch.y);

        switch (ev->type) {
            case sf::Event::TouchBegan:
                //m_twoFingerScroll.reportFingerDown(fingerId, x, y); // FIXME
                break;

            case sf::Event::TouchEnded:
                // m_twoFingerScroll.reportFingerUp(fingerId); // FIXME
                break;

            case sf::Event::TouchMoved:
            default:
                // FIXME
                // m_twoFingerScroll.reportFingerMotion(fingerId, x, y);
                // if (m_twoFingerScroll.isScrolling())
                //    return handleTwoFingerScroll(wasScrolling);
                break;
        }
    }

    // if ((event.type == Event::Type::MouseButtonPressed) && (sfmlEvent.type == sf::Event::TouchBegan)) {
    //     // For touches, always send a mouse move event before the mouse press,
    //     // because widgets may assume that the mouse had to move to the clicked location first
    //     Event mouseMoveEvent;
    //     mouseMoveEvent.type = Event::Type::MouseMoved;
    //     mouseMoveEvent.mouseMove.x = event.mouseButton.x;
    //     mouseMoveEvent.mouseMove.y = event.mouseButton.y;
    //     handleEvent(mouseMoveEvent);
    // }

    switch (ev->type) {
        case sf::Event::MouseMoved:
            //LOGD("MouseMoved", "position={},{}", ev->mouseMove.x, ev->mouseMove.y);
            break;
        case sf::Event::MouseButtonPressed:
        case sf::Event::MouseButtonReleased:
            LOGD(ev->type == sf::Event::MouseButtonPressed
                ? "MouseButtonPressed"
                : "MouseButtonReleased"
                , "position={},{}; button={}"
                , ev->mouseButton.x, ev->mouseButton.y
                , ev->mouseButton.button == sf::Mouse::Button::Left
                    ? "left"
                    : ev->mouseButton.button == sf::Mouse::Button::Right
                        ? "right"
                        : ev->mouseButton.button == sf::Mouse::Button::Middle
                            ? "middle"
                            : ev->mouseButton.button == sf::Mouse::Button::XButton1
                                ? "xbutton1"
                                : ev->mouseButton.button == sf::Mouse::Button::XButton2
                                    ? "xbutton2"
                                    : "<unknown>");
            break;
        case sf::Event::MouseWheelScrolled: {
            // delta:
            //      -1 - wheel down
            //       1 - wheel up
            LOGD("MouseWheelScrolled", "position={},{}; delta={}"
                , ev->mouseWheelScroll.x, ev->mouseWheelScroll.y
                , ev->mouseWheelScroll.delta);

            // switch (event.type) {
            //     case Event::Type::MouseMoved:
            //         return m_container->processMouseMoveEvent(mouseCoords);
            //
            //     case Event::Type::MouseWheelScrolled:
            //         if (m_container->processScrollEvent(event.mouseWheel.delta, mouseCoords, false))
            //             return true;
            //
            //         // Even if no scrollbar moved, we will still absorb the scroll event when the mouse is on top of a widget
            //         return m_container->getWidgetAtPos(mouseCoords, false) != nullptr;
            //
            //     case Event::Type::MouseButtonPressed:
            //         return m_container->processMousePressEvent(event.mouseButton.button, mouseCoords);
            //
            //     case Event::Type::MouseButtonReleased: {
            //         bool const eventHandled = m_container->processMouseReleaseEvent(event.mouseButton.button, mouseCoords);
            //
            //         if (event.mouseButton.button == Event::MouseButton::Left)
            //             m_container->leftMouseButtonNoLongerDown();
            //         else if (event.mouseButton.button == Event::MouseButton::Right)
            //             m_container->rightMouseButtonNoLongerDown();
            //
            //         return eventHandled;
            //     }
                break;
            }

        case sf::Event::Closed:
            _running = false;
            break;

        case sf::Event::Resized: {
            _win_w = ev->size.width;
            _win_h = ev->size.height;

            // Update the view to the new size of the window
            sf::FloatRect visibleArea(0, 0, _win_w, _win_h);
            _win->setView(sf::View(visibleArea));

            //LOGD("sf::Event::Resized: {}x{}", _win_w, _win_h);
            _update_required = true;
            break;
        }

        case sf::Event::KeyPressed: {
            LOGD("~~~", "KEY PRESSED: {}", static_cast<std::underlying_type<sf::Keyboard::Key>::type>(ev->key.code));
            // FIXME
            if (/*isTabKeyUsageEnabled() && */(ev->key.code == sf::Keyboard::Tab)) {
            //     if (event.key.shift)
            //         focusPreviousWidget(true);
            //     else
            //         focusNextWidget(true);
            //
            //     return true;
            } else {
            //     return m_container->processKeyPressEvent(event.key);
            }

            break;
        }

        case sf::Event::TextEntered:
            LOGD("---", "TEXT ENTERED: {}", ev->text.unicode);
            // FIXME
            // return m_container->processTextEnteredEvent(event.text.unicode);
            break;

        // Window lost focus
        case sf::Event::LostFocus:
            // FIXME
            // m_windowFocused = false;
            // onWindowUnfocus.emit(m_container.get());
            break;

        // Window gained focus
        case sf::Event::GainedFocus:
            // FIXME
            // m_windowFocused = true;
            // onWindowFocus.emit(m_container.get());
            break;

        case sf::Event::MouseEntered:
            break;

        case sf::Event::MouseLeft:
            // FIXME
            // m_container->mouseNoLongerOnWidget();
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
    std::chrono::microseconds micros_per_frame {1000000 / 60};
    pfs::countdown_timer<std::micro, std::int32_t> countdown_timer{micros_per_frame};

    while (_running) {
        countdown_timer.reset();
        step();
        std::this_thread::sleep_for(countdown_timer.remain());
    }
}

}} // namespace griotte::SFML
