#pragma once
#include <QWidget>

QT_BEGIN_NAMESPACE
class QPaintEvent;
QT_END_NAMESPACE

class Surface : public QWidget
{
public:
    Surface (QWidget * parent = 0) : QWidget(parent) {}

protected:
    void paintEvent (QPaintEvent * event) override;
};

