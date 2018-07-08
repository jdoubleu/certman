#include <src/gui/window/MainWindow.h>
#include <QApplication>
#include "Application.h"

using gui::window::MainWindow;

using namespace core;

Application::Application() : crtMgr(new CertificateManager()) {
}

Application::~Application() {
    delete crtMgr;
}

int Application::run(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // application meta information
    a.setOrganizationName("certman");
    a.setApplicationName("certman");
    a.setOrganizationDomain("certman.it-sec.medien.hs-duesseldorf.de");

    MainWindow w(crtMgr);
    w.show();

    return a.exec();
}
