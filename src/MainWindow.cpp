#include <QApplication>
#include <QCloseEvent>
#include <QSettings>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include "Surface.hpp"
#include "MainWindow.hpp"
#include "pfs/griotte/painter/qt.hpp"

#include <QDebug>

static QString const GEOMETRY_KEY("geometry");
static QString const WINDOW_STATE_KEY("window-state");

MainWindow::MainWindow ()
    : QMainWindow(0)
{
    //auto layout = new QVBoxLayout(this);
    _surface = new Surface(this);
    setCentralWidget(_surface);

    initActions();
    initMenus();
    initStatusBar();
    restoreSettings();
}

void MainWindow::closeEvent (QCloseEvent * event)
{
    saveSettings();
    event->accept();
}

void MainWindow::initActions ()
{
    _exitAct = new QAction(tr("Exit"), this);
    _exitAct->setShortcuts(QKeySequence::Quit);
    _exitAct->setStatusTip(tr("Exit from application"));
    connect(_exitAct, SIGNAL(triggered()), this, SLOT(onExit()));
}

void MainWindow::initMenus ()
{
    _fileMenu = menuBar()->addMenu(tr("File"));
    _fileMenu->addAction(_exitAct);
}

void MainWindow::initStatusBar ()
{
    // TODO
}

void MainWindow::saveSettings ()
{
    QSettings settings(qApp->organizationName(), qApp->applicationName());
    settings.setValue(GEOMETRY_KEY, saveGeometry());
    settings.setValue(WINDOW_STATE_KEY, saveState());
}

void MainWindow::restoreSettings ()
{
    QSettings settings(qApp->organizationName(), qApp->applicationName());

    this->restoreGeometry(settings.value(GEOMETRY_KEY).toByteArray());
    this->restoreState(settings.value(WINDOW_STATE_KEY).toByteArray());
}

void MainWindow::onExit ()
{
    qApp->closeAllWindows();
}

