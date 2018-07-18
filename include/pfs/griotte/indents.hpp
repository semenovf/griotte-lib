#pragma once

namespace pfs {
namespace griotte {

template <typename UnitT>
class indents
{
public:
    using unit_type = UnitT;

private:
    unit_type _top;
    unit_type _right;
    unit_type _bottom;
    unit_type _left;

public:
    indents () noexcept
        : _top(0), _right(0), _bottom(0), _left(0) {}

    indents (unit_type top, unit_type right, unit_type bottom, unit_type left) noexcept
        : _top(top), _right(right), _bottom(bottom), _left(left) {}

    ~indents () = default;
    indents (indents const & rhs) = default;
    indents & operator = (indents const & rhs) = default;
    indents (indents && rhs) = default;
    indents & operator = (indents && rhs) = default;

    unit_type get_top () const noexcept { return _top; }
    unit_type get_right () const noexcept { return _right; }
    unit_type get_bottom () const noexcept { return _bottom; }
    unit_type get_left () const noexcept { return _left; }
};

template <typename UnitT>
using margins = indents<UnitT>;

template <typename UnitT>
using paddings = indents<UnitT>;

}} // namespace pfs::griotte
