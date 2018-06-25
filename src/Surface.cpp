#include <QPaintEvent>
#include <QPainter>
#include "Surface.hpp"

void Surface::paintEvent (QPaintEvent * event)
{
    QPainter p(this);
    p.fillRect(rect(), {80, 80, 255, 128});
}
