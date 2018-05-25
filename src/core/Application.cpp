#include <src/gui/window/MainWindow.h>
#include <QApplication>
#include "Application.h"

using gui::window::MainWindow;

int core::Application::run(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
