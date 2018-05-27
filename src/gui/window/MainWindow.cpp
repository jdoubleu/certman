#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "../assistant/ImportAssistant.h"
#include "../../cert/CertificateManager.h"

using gui::assistant::ImportAssistant;
using cert::CertificateManager;

using namespace gui::window;

MainWindow::MainWindow(CertificateManager *crtMgr, Environment *env, QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow),
        crtList(new CertificateListWidget(this)),
        crtMgr(crtMgr), env(env) {
    ui->setupUi(this);

    this->setupActions();

    ui->centralwidget->layout()->addWidget(crtList);

    crtMgr->loadCertificates();
    onCertificateImport(true);
}

MainWindow::~MainWindow() {
    delete ui;
    delete crtList;
}

void MainWindow::setupActions() {
    connect(ui->action_Import, SIGNAL(triggered()), this, SLOT(importCertificate()));
}

void MainWindow::importCertificate() {
    ImportAssistant ia(crtMgr);

    connect(&ia, SIGNAL(certificateImported(bool)), this, SLOT(onCertificateImport(bool)));

    ia.exec();
}

void MainWindow::onCertificateImport(bool successful) {
    if (successful) {
        crtList->showCertificates(*crtMgr->getCertificateList()->listAll());
    }
}
