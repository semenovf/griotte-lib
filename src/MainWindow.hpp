#pragma once
#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QCloseEvent;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QWidget * _surface;
    QMenu * _fileMenu;
    QAction * _exitAct;

public:
    MainWindow ();

protected:
    virtual void closeEvent (QCloseEvent *) override;

private:
    void initActions ();
    void initMenus ();
    void initStatusBar ();
    void saveSettings ();
    void restoreSettings ();

private:
    Q_SLOT void onExit ();
};
