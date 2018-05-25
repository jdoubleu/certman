#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "../assistant/ImportAssistant.h"
#include "src/gui/widget/CertificateListWidget.h"
#include "../../cert/CertificateManager.h"

using gui::assistant::ImportAssistant;
using gui::widget::CertificateListWidget;
using cert::CertificateManager;

using namespace gui::window;

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);

    this->setupActions();

    auto *list = new CertificateListWidget(this);
    ui->centralwidget->layout()->addWidget(list);

    auto crtMgr = new CertificateManager();
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
    ImportAssistant ia;
    ia.exec();
}
