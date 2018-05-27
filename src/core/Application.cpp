#include <src/gui/window/MainWindow.h>
#include <QApplication>
#include "Application.h"

using gui::window::MainWindow;

using namespace core;

Application::Application(): crtMgr(new CertificateManager()), env(new Environment()) {
}

Application::~Application() {
    delete crtMgr;
    delete env;
}

int Application::run(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w(crtMgr, env);
    w.show();

    return a.exec();
}
