#pragma once
#include <pfs/griotte/unit.hpp>

namespace pfs {
namespace griotte {

class argb_color
{
    uint8_t _alpha;
    uint8_t _red;
    uint8_t _green;
    uint8_t _blue;

public:
    argb_color () noexcept
        : _alpha(0)
        , _red(0)
        , _green(0)
        , _blue(0)
    {}

    argb_color (int red, int green, int blue, int alpha = 255) noexcept
        : _alpha(static_cast<uint8_t>(alpha))
        , _red(static_cast<uint8_t>(red))
        , _green(static_cast<uint8_t>(green))
        , _blue(static_cast<uint8_t>(blue))
    {}

    argb_color (argb_color const & rhs) = default;
    argb_color & operator = (argb_color const & rhs) = default;

    constexpr int alpha () const noexcept { return _alpha; }
    constexpr int red ()   const noexcept { return _red; }
    constexpr int green () const noexcept { return _green; }
    constexpr int blue ()  const noexcept { return _blue; }
};

using color = argb_color;

}} // namespace pfs::griotte

