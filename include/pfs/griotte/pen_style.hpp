#pragma once

namespace pfs {
namespace griotte {

enum class pen_line_style : int
{
      no_pen       = 0 ///!<No line at all.
    , solid        = 1 ///!<A plain line.
    , dash         = 2 ///!<Dashes separated by a few pixels.
    , dot          = 3 ///!<Dots separated by a few pixels.
    , dash_dot     = 4 ///!<Alternate dots and dashes.
    , dash_dot_dot = 5 ///!<One dash, two dots, one dash, two dots.
};

enum class pen_cap_style : int
{
      flat   = 0x00 ///!<A square line end that does not cover the end point of the line.
    , square = 0x10 ///!<A square line end that covers the end point and extends beyond it by half the line width.
    , round  = 0x20 ///!<A rounded line end.
};

enum class pen_join_style : int
{
      miter     = 0x00  ///!<The outer edges of the lines are extended to meet at an angle, and this area is filled.
    , bevel     = 0x40  ///!<The triangular notch between the two lines is filled.
    , round     = 0x80  ///!<A circular arc between the two lines is filled.
    , svg_miter = 0x100 ///!<A miter join corresponding to the definition of a miter join in the SVG 1.2 Tiny specification.
};

}} // namespace pfs::griotte
