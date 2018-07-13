#pragma once
#include <vector>
#include <pfs/griotte/color.hpp>

namespace pfs {
namespace griotte {

class stroke
{
public:
    enum class cap_style : int
    {
          butt   = 0x00 ///!<A square line end that does not cover the end point of the line.
        , flat   = butt ///!<Synonym for butt.
        , square = 0x10 ///!<A square line end that covers the end point and extends beyond it by half the line width.
        , round  = 0x20 ///!<A rounded line end.
    };

    using dasharray_type = vector<int>;

private:
    color          _color;
    int            _width;
    cap_style      _cap;
    dasharray_type _dasharray; // empty means solid line

public:
    /**
     * @brief Constructs an invisible stroke.
     */
    stroke () noexcept
        : _color{0, 0, 0, 0}
        , _width(0)
    {}

    /**
     * @brief Constructs a path with start point at @a start.
     */
    stroke (color const & acolor, int width = 1, cap_style acap = cap_style::butt) noexcept
        : _color(acolor)
        , _width(width)
        , _cap(acap)
    {}

    ~stroke () = default;
    stroke (stroke const & rhs) = default;
    stroke & operator = (stroke const & rhs) = default;
    stroke (stroke && rhs) = default;
    stroke & operator = (stroke && rhs) = default;
};

}} // namespace pfs::griotte



