#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "../assistant/ImportAssistant.h"
#include "../assistant/ExportAssistant.h"
#include "../widget/CertificateDetailWidget.h"

using cert::CertificateManager;
using gui::assistant::ImportAssistant;
using gui::assistant::ExportAssistant;
using gui::widget::CertificateDetailWidget;

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

    connect(crtList, SIGNAL(certificateSelected(Certificate * )), this, SLOT(onCertificateSelected(Certificate * )));
    connect(crtList, SIGNAL(certificatesSelected(vector<Certificate *>)), this,
            SLOT(onCertificatesSelected(vector<Certificate *>)));

    connect(ui->actionDetails, SIGNAL(triggered()), this, SLOT(onCertificateDetailsAction()));
    connect(ui->actionExport, SIGNAL(triggered()), this, SLOT(onCertificateExportAction()));
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

void MainWindow::onCertificateSelected(Certificate *cert) {
    auto detail = CertificateDetailWidget::asDialog(*cert, this);
    detail->show();
}

void MainWindow::onCertificatesSelected(vector<Certificate *> certificates) {
    if (certificates.empty()) {
        // Disable some certificate actions in menu
        ui->actionDetails->setDisabled(true);
        ui->actionExport->setDisabled(true);

        selectedCertificate = NULL;
    } else {
        // TODO: support multiple certificates
        selectedCertificate = certificates[0];

        ui->actionDetails->setDisabled(false);
        ui->actionExport->setDisabled(false);
    }
}

void MainWindow::onCertificateDetailsAction() {
    if (selectedCertificate != NULL) {
        onCertificateSelected(selectedCertificate);
    }
}

void MainWindow::onCertificateExportAction() {
    if (selectedCertificate != NULL) {
        ExportAssistant ea(crtMgr, selectedCertificate);
        ea.exec();
    }
}
