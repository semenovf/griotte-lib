#include <QPaintEvent>
#include <pfs/griotte/painter.hpp>
#include <pfs/griotte/stroker.hpp>
#include "Surface.hpp"

using unit_t  = int;
using point   = pfs::griotte::point<unit_t>;
using rect    = pfs::griotte::rect<unit_t>;
using pen     = pfs::griotte::pen<unit_t>;
using path    = pfs::griotte::path<unit_t>;
using stroker = pfs::griotte::stroker<unit_t>;

void Surface::paintEvent (QPaintEvent * event)
{
    pfs::griotte::painter p{this};
    pfs::griotte::color black{0, 0, 0, 255};
    pfs::griotte::color red{255, 0, 0, 255};
    pfs::griotte::color green{0, 255, 0, 255};
    pfs::griotte::color blue{0, 0, 255, 255};

//     pen default_pen(black, 3.0f);
//
//     ::point p1{20, 20};
//     ::point p2{120, 120};
//
//     p.draw_line(p1, p2, default_pen);
//
//     default_pen.add_dash(5);
//     default_pen.add_dash(5);
//
//     p.draw_line(::point{100, 20}, ::point{315, 20}, default_pen);
//
//     default_pen.clear_dasharray();
//     default_pen.add_dash(10);
//     default_pen.add_dash(10);
//
//     p.draw_line(::point{100, 40}, ::point{315, 40}, default_pen);
//
//     default_pen.clear_dasharray();
//     default_pen.add_dash(20);
//     default_pen.add_dash(10);
//     default_pen.add_dash(5);
//     default_pen.add_dash(5);
//     default_pen.add_dash(5);
//     default_pen.add_dash(10);
//     p.draw_line(::point{100, 60}, ::point{315, 60}, default_pen);
//
//     // Draw curves with absolute coordinates
//     {
//         path path1;
//         pen pen1(red, 1.0f);
//         path1.move_to(point{0, 0});
//         path1.curve_to(point{99, 0},  point{50, 50}, point{99, 99});
//         path1.curve_to(point{0, 99},  point{50, 50}, point{0, 0});
//
//         stroker stroker1(path1);
//         stroker1.outline(p, pen1);
//     }
//
//
//     // Draw curves with relative coordinates
//     {
//         path path1;
//         pen pen1(red, 1.0f);
//         bool relative = true;
//         path1.move_to(point{200, 200});
//         path1.curve_to(point{99, 0},  point{50, 50}, point{99, 99}, relative);
//         path1.curve_to(point{0, 99},  point{50, 50}, point{0, 0}, relative);
//
//         stroker stroker1(path1);
//         stroker1.outline(p, pen1);
//     }

    {
        path path1;
        path path2;
        path path3;
        path path4;
        bool relative = true;

        pen pen1{red, 10};
        pen pen2{pen1};
        pen pen3{green, 3};
        pen pen4{blue, 5};

        path1.move_to(100, 350);
        path1.line_to(150, -300, relative);
        path1.line_to(50, 50, relative);
        path1.vline_to(50, relative);
        path1.line_to(5, 5);

//         path2.move_to(250, 50);
//         path2.line_to(150, 300, relative);
//
//         path3.move_to(175, 200);
//         path3.line_to(150, 0, relative);
//
//         path4.move_to(100, 350);
//         //path4.quad_to(150, -300, 300, 0, relative);
//         path4.cubic_to(175, 200, 325, 200, 400, 350);
//         //path4.quad_to(250, 50, 400, 350);

        stroker{path1}.stroke(p, pen1);
//         stroker{path2}.stroke(p, pen2);
//         stroker{path3}.stroke(p, pen3);
//         stroker{path4}.stroke(p, pen4);
    }
}
