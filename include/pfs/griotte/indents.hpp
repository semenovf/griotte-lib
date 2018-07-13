#pragma once
#include <pfs/griotte/unit.hpp>

namespace pfs {
namespace griotte {

class indents
{
    unit _top;
    unit _right;
    unit _bottom;
    unit _left;

public:
    indents () noexcept
        : _top(0), _right(0), _bottom(0), _left(0) {}

    indents (unit top, unit right, unit bottom, unit left) noexcept
        : _top(top), _right(right), _bottom(bottom), _left(left) {}

    indents (indents const & rhs) = default;
    indents & operator = (indents const & rhs) = default;

    unit top () const noexcept { return _top; }
    unit right () const noexcept { return _right; }
    unit bottom () const noexcept { return _bottom; }
    unit left () const noexcept { return _left; }
};

using margins = indents;
using paddings = indents;

}} // namespace pfs::griotte
