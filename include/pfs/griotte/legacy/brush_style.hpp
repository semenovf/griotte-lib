#pragma once

//FIXME __DEPRECATED__
#if __DEPRECATED__

namespace pfs {
namespace griotte {

enum class brush_pattern_style : int
{
      no_brush         =  0 ///!<No brush pattern.
    , solid            =  1 ///!<Uniform color.
    , dense1           =  2 ///!<Extremely dense brush pattern.
    , dense2           =  3 ///!<Very dense brush pattern.
    , dense3           =  4 ///!<Somewhat dense brush pattern.
    , dense4           =  5 ///!<Half dense brush pattern.
    , dense5           =  6 ///!<Somewhat sparse brush pattern.
    , dense6           =  7 ///!<Very sparse brush pattern.
    , dense7           =  8 ///!<Extremely sparse brush pattern.
    , horizontal       =  9 ///!<Horizontal lines.
    , vertical         = 10 ///!<Vertical lines.
    , cross            = 11 ///!<Crossing horizontal and vertical lines.
    , backward_diag    = 12 ///!<Backward diagonal lines.
    , forward_diag     = 13 ///!<Forward diagonal lines.
    , cross_diag       = 14 ///!<Crossing diagonal lines.
    , linear_gradient  = 15 ///!<Linear gradient (set using a dedicated QBrush constructor).
    , conical_gradient = 17 ///!<Conical gradient (set using a dedicated QBrush constructor).
    , radial_gradient  = 16 ///!<Radial gradient (set using a dedicated QBrush constructor).
    , texture          = 24 ///!<Custom pattern (see brush::set_texture()).
};

}} // namespace pfs::griotte

#endif
