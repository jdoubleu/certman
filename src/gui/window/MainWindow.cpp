#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "../assistant/ImportAssistant.h"
#include "src/gui/widget/CertificateListWidget.h"
#include "../../cert/CertificateManager.h"

using gui::assistant::ImportAssistant;
using gui::widget::CertificateListWidget;
using cert::CertificateManager;

using namespace gui::window;

MainWindow::MainWindow(CertificateManager *crtMgr, Environment *env, QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow),
        crtMgr(crtMgr), env(env) {
    ui->setupUi(this);

    this->setupActions();

    auto *list = new CertificateListWidget(this);
    ui->centralwidget->layout()->addWidget(list);

    crtMgr->loadCertificates();
    list->showCertificates(*crtMgr->getCertificateList());
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setupActions() {
    connect(ui->action_Import, SIGNAL(triggered()), this, SLOT(importCertificate()));
}

void MainWindow::importCertificate() {
    ImportAssistant ia(crtMgr);
    ia.exec();
}
