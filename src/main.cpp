#include "gui/window/MainWindow.h"
#include <QApplication>

using gui::window::MainWindow;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
