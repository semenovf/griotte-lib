#pragma once
#include <QPainter>
#include <pfs/griotte/color.hpp>
#include <pfs/griotte/pen_style.hpp>
#include <pfs/griotte/brush_style.hpp>
#include <pfs/griotte/line.hpp>
#include <pfs/griotte/rect.hpp>

namespace pfs {
namespace griotte {
namespace qt {

class brush;
class pen;
class painter;

// No need to call this function anywhere. This assertions process at compile-time.
constexpr inline bool pen_line_style_asserter ()
{
    static_assert(static_cast<int>(pen_line_style::no_pen)       == Qt::NoPen         , "value of 'pen_line_style::no_pen' is not corresponds to 'Qt::NoPen'");
    static_assert(static_cast<int>(pen_line_style::solid)        == Qt::SolidLine     , "value of 'pen_line_style::solid' is not corresponds to 'Qt::SolidLine'");
    static_assert(static_cast<int>(pen_line_style::dash)         == Qt::DashLine      , "value of 'pen_line_style::dash' is not corresponds to 'Qt::DashLine'");
    static_assert(static_cast<int>(pen_line_style::dot)          == Qt::DotLine       , "value of 'pen_line_style::dot' is not corresponds to 'Qt::DotLine'");
    static_assert(static_cast<int>(pen_line_style::dash_dot)     == Qt::DashDotLine   , "value of 'pen_line_style::dash_dot' is not corresponds to 'Qt::DashDotLine'");
    static_assert(static_cast<int>(pen_line_style::dash_dot_dot) == Qt::DashDotDotLine, "value of 'pen_line_style::dash_dot_dot' is not corresponds to 'Qt::DashDotDotLine'");
    return true;
};

// No need to call this function anywhere. This assertions process at compile-time.
constexpr inline bool pen_cap_style_asserter ()
{
    static_assert(static_cast<int>(pen_cap_style::flat)   == Qt::FlatCap  , "value of 'pen_cap_style::flat' is not corresponds to 'Qt::FlatCap'");
    static_assert(static_cast<int>(pen_cap_style::square) == Qt::SquareCap, "value of 'pen_cap_style::square' is not corresponds to 'Qt::SquareCap'");
    static_assert(static_cast<int>(pen_cap_style::round)  == Qt::RoundCap , "value of 'pen_cap_style::round' is not corresponds to 'Qt::RoundCap'");
    return true;
};

// No need to call this function anywhere. This assertions process at compile-time.
constexpr inline bool pen_join_style_asserter ()
{
    static_assert(static_cast<int>(pen_join_style::miter)     == Qt::MiterJoin   , "value of 'pen_join_style::miter' is not corresponds to 'Qt::MiterJoin'");
    static_assert(static_cast<int>(pen_join_style::bevel)     == Qt::BevelJoin   , "value of 'pen_join_style::bevel' is not corresponds to 'Qt::BevelJoin'");
    static_assert(static_cast<int>(pen_join_style::round)     == Qt::RoundJoin   , "value of 'pen_join_style::round' is not corresponds to 'Qt::RoundJoin'");
    static_assert(static_cast<int>(pen_join_style::svg_miter) == Qt::SvgMiterJoin, "value of 'pen_join_style::svg_miter' is not corresponds to 'Qt::SvgMiterJoin'");
    return true;
};

// No need to call this function anywhere. This assertions process at compile-time.
constexpr inline bool brush_pattern_style_asserter ()
{
    static_assert(static_cast<int>(brush_pattern_style::no_brush)         == Qt::NoBrush               , "value of 'brush_pattern_style::no_brush' is not corresponds to 'Qt::NoBrush'");
    static_assert(static_cast<int>(brush_pattern_style::solid)            == Qt::SolidPattern          , "value of 'brush_pattern_style::solid' is not corresponds to 'Qt::SolidPattern'");
    static_assert(static_cast<int>(brush_pattern_style::dense1)           == Qt::Dense1Pattern         , "value of 'brush_pattern_style::dense1' is not corresponds to 'Qt::Dense1Pattern'");
    static_assert(static_cast<int>(brush_pattern_style::dense2)           == Qt::Dense2Pattern         , "value of 'brush_pattern_style::dense2' is not corresponds to 'Qt::Dense2Pattern'");
    static_assert(static_cast<int>(brush_pattern_style::dense3)           == Qt::Dense3Pattern         , "value of 'brush_pattern_style::dense3' is not corresponds to 'Qt::Dense3Pattern'");
    static_assert(static_cast<int>(brush_pattern_style::dense4)           == Qt::Dense4Pattern         , "value of 'brush_pattern_style::dense4' is not corresponds to 'Qt::Dense4Pattern'");
    static_assert(static_cast<int>(brush_pattern_style::dense5)           == Qt::Dense5Pattern         , "value of 'brush_pattern_style::dense5' is not corresponds to 'Qt::Dense5Pattern'");
    static_assert(static_cast<int>(brush_pattern_style::dense6)           == Qt::Dense6Pattern         , "value of 'brush_pattern_style::dense6' is not corresponds to 'Qt::Dense6Pattern'");
    static_assert(static_cast<int>(brush_pattern_style::dense7)           == Qt::Dense7Pattern         , "value of 'brush_pattern_style::dense7' is not corresponds to 'Qt::Dense7Pattern'");
    static_assert(static_cast<int>(brush_pattern_style::horizontal)       == Qt::HorPattern            , "value of 'brush_pattern_style::horizontal' is not corresponds to 'Qt::HorPattern'");
    static_assert(static_cast<int>(brush_pattern_style::vertical)         == Qt::VerPattern            , "value of 'brush_pattern_style::vertical' is not corresponds to 'Qt::VerPattern'");
    static_assert(static_cast<int>(brush_pattern_style::cross)            == Qt::CrossPattern          , "value of 'brush_pattern_style::cross' is not corresponds to 'Qt::CrossPattern'");
    static_assert(static_cast<int>(brush_pattern_style::backward_diag)    == Qt::BDiagPattern          , "value of 'brush_pattern_style::backward_diag' is not corresponds to 'Qt::BDiagPattern'");
    static_assert(static_cast<int>(brush_pattern_style::forward_diag)     == Qt::FDiagPattern          , "value of 'brush_pattern_style::forward_diag' is not corresponds to 'Qt::FDiagPattern'");
    static_assert(static_cast<int>(brush_pattern_style::cross_diag)       == Qt::DiagCrossPattern      , "value of 'brush_pattern_style::cross_diag' is not corresponds to 'Qt::DiagCrossPattern'");
    static_assert(static_cast<int>(brush_pattern_style::linear_gradient)  == Qt::LinearGradientPattern , "value of 'brush_pattern_style::linear_gradient' is not corresponds to 'Qt::LinearGradientPattern'");
    static_assert(static_cast<int>(brush_pattern_style::conical_gradient) == Qt::ConicalGradientPattern, "value of 'brush_pattern_style::conical_gradient' is not corresponds to 'Qt::ConicalGradientPattern'");
    static_assert(static_cast<int>(brush_pattern_style::radial_gradient)  == Qt::RadialGradientPattern , "value of 'brush_pattern_style::radial_gradient' is not corresponds to 'Qt::RadialGradientPattern'");
    static_assert(static_cast<int>(brush_pattern_style::texture)          == Qt::TexturePattern        , "value of 'brush_pattern_style::texture' is not corresponds to 'Qt::TexturePattern'");

    return true;
};

class brush
{
    friend class painter;
    friend class pen;

    QBrush _b;

public:
    brush () {}
    brush (color const & acolor
            , brush_pattern_style pattern = brush_pattern_style::solid)
        : _b(QColor(acolor.red(), acolor.green(), acolor.blue(), acolor.alpha())
                , static_cast<Qt::BrushStyle>(pattern))
    {}
};

class pen
{
    friend class painter;

    QPen _p;

public:
    pen () {}
    pen (brush const & abrush, double width
            , pen_line_style astyle = pen_line_style::solid
            , pen_cap_style cap = pen_cap_style::square
            , pen_join_style join = pen_join_style::bevel)
        : _p(abrush._b
                , width
                , static_cast<Qt::PenStyle>(astyle)
                , static_cast<Qt::PenCapStyle>(cap)
                , static_cast<Qt::PenJoinStyle>(join))
    {}
};

class painter
{
    QPainter _p;

public:
    painter (QPaintDevice * pd) : _p(pd) {}

    /**
     * @fn void painter::set_pen (pen const & apen)
     * @brief Sets the pen to be the given @a apen.
     * @param apen The pen.
     */
    void set_pen (pen const & apen)
    {
        _p.setPen(apen._p);
    }

    /**
     * @fn void painter::set_brush (brush const & abrush)
     * @brief Sets the brush to the given @a abrush.
     * @param abrush The brush.
     */
    void set_brush (brush const & abrush)
    {
        _p.setBrush(abrush._b);
    }


//     /**
//      * @fn void painter::draw_arc (rect const & arect, int start_angle, int span_angle)
//      * @brief Draws the arc.
//      * @details Positive values for the angles mean counter-clockwise while
//      *          negative values mean the clockwise direction. Zero degrees is
//      *          at the 3 o'clock position.
//      * @param rect Center position of the arc.
//      * @param start_angle The start angle in radians.
//      * @param span_angle The span angle in radians.
//      */
//     inline void draw_arc (point const & center
//             , double radius
//             , int start_angle
//             , int span_angle)
//     {
//         int start_angle_degrees = 0;
//         int span_angle_degrees  = 0;
//
//         _p.drawArc(arect.x(), arect.y()
//                 , arect.width(), arect.height()
//                 , start_angle_degrees, span_angle_degrees);
//     }

    /**
     * @fn void painter::draw_line (line const & aline)
     * @brief Draws a line defined by @ aline.
     * @param aline The line to draw.
     */
    template <typename UnitT>
    inline void draw_line (line<UnitT> const & aline)
    {
        point<UnitT> p1 = aline.p1();
        point<UnitT> p2 = aline.p2();
        _p.drawLine(p1.x(), p1.y(), p2.x(), p2.y());
    }

    /**
     * @fn void painter::draw_line (point const & p1, point const & p2)
     * @brief Draws a line from point @a p1 to point @a p2.
     * @param p1 The start point.
     * @param p2 The end point.
     */
    template <typename UnitT>
    inline void draw_line (point<UnitT> const & p1
            , point<UnitT> const & p2)
    {
        _p.drawLine(p1.x(), p1.y(), p2.x(), p2.y());
    }

    /**
     * @fn void painter::draw_rect (rect const & arect)
     * @brief Draws the rectangle @a rect with the current pen and brush.
     * @param arect Rectangle to draw.
     */
    template <typename UnitT>
    inline void draw_rect (rect<UnitT> const & arect)
    {
        _p.drawRect(arect.x(), arect.y(), arect.width(), arect.height());
    }
};

}}} // namespace pfs::griotte::qt
