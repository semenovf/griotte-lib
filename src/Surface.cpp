#include <QPaintEvent>
#include <pfs/griotte/painter.hpp>
#include "Surface.hpp"

using point = pfs::griotte::point<int>;
using rect = pfs::griotte::rect<int>;

void Surface::paintEvent (QPaintEvent * event)
{
    pfs::griotte::painter p{this};
    pfs::griotte::color black{0, 0, 0, 255};
    pfs::griotte::brush brush{black, pfs::griotte::brush_pattern_style::solid};
    pfs::griotte::pen pen{brush, 3.0f};

    p.set_pen(pen);

    ::point p1{20, 20};
    ::point p2{120, 120};

    p.draw_line(p1, p2);

    ::rect r{100, 20, 100, 70};

    p.draw_rect(r);


    //p.fillRect(rect(), {80, 80, 255, 128});
}
