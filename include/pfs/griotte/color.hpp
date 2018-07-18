#pragma once

namespace pfs {
namespace griotte {

class rgba_color
{
    uint8_t _alpha;
    uint8_t _red;
    uint8_t _green;
    uint8_t _blue;

public:
    constexpr rgba_color () noexcept
        : _alpha(0)
        , _red(0)
        , _green(0)
        , _blue(0)
    {}

    constexpr rgba_color (int red, int green, int blue, int alpha = 255) noexcept
        : _alpha(static_cast<uint8_t>(alpha))
        , _red(static_cast<uint8_t>(red))
        , _green(static_cast<uint8_t>(green))
        , _blue(static_cast<uint8_t>(blue))
    {}

    rgba_color (rgba_color const & rhs) = default;
    rgba_color & operator = (rgba_color const & rhs) = default;

    constexpr int get_alpha () const noexcept { return _alpha; }
    constexpr int get_red ()   const noexcept { return _red; }
    constexpr int get_green () const noexcept { return _green; }
    constexpr int get_blue ()  const noexcept { return _blue; }
};

using color = rgba_color;

}} // namespace pfs::griotte

