#include <QApplication>
#include "MainWindow.hpp"

int main (int argc, char * argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName("jobquest.ru");
    app.setApplicationName("griotte");

    MainWindow mainWin;
    mainWin.show();

    int r = app.exec();
    return r;
}
