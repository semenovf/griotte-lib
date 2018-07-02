#pragma once
#include <pfs/griotte/unit.hpp>

namespace pfs {
namespace griotte {

class indents
{
    unit_t _top;
    unit_t _right;
    unit_t _bottom;
    unit_t _left;

public:
    indents () noexcept
        : _top(0), _right(0), _bottom(0), _left(0) {}

    indents (unit_t top, unit_t right, unit_t bottom, unit_t left) noexcept
        : _top(top), _right(right), _bottom(bottom), _left(left) {}

    indents (indents const & rhs) = default;
    indents & operator = (indents const & rhs) = default;

    constexpr unit_t top () const noexcept { return _top; }
    constexpr unit_t right () const noexcept { return _right; }
    constexpr unit_t bottom () const noexcept { return _bottom; }
    constexpr unit_t left () const noexcept { return _left; }
};

using margins = indents;
using paddings = indents;

}} // namespace pfs::griotte
