#include <QMessageBox>
#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "../assistant/ImportAssistant.h"
#include "../assistant/ExportAssistant.h"
#include "../widget/CertificateDetailWidget.h"
#include "../assistant/CreateCertificateAssistant.h"
#include "../assistant/CreateCACertificateAssistant.h"
#include "../assistant/SignAssistant.h"

using cert::CertificateManager;
using gui::assistant::ImportAssistant;
using gui::assistant::ExportAssistant;
using gui::assistant::SignAssistant;
using gui::widget::CertificateDetailWidget;
using gui::assistant::CreateCertificateAssistant;
using gui::assistant::CreateCACertificateAssistant;
using cert::CERT_EXPORT;

using namespace gui::window;

MainWindow::MainWindow(CertificateManager *crtMgr, QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow),
        crtList(new CertificateListWidget(this)),
        crtMgr(crtMgr) {
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
    connect(ui->actionNew_Certificate, &QAction::triggered, this, &MainWindow::onNewCertificateAction);
    connect(ui->actionNew_Certificate_Authority, &QAction::triggered, this,
            &MainWindow::onNewCertificateAuthorityAction);

    connect(crtList, SIGNAL(certificateSelected(Certificate * )), this, SLOT(onCertificateSelected(Certificate * )));
    connect(crtList, SIGNAL(certificatesSelected(vector<Certificate *>)), this,
            SLOT(onCertificatesSelected(vector<Certificate *>)));
    connect(crtList, SIGNAL(certificateRemoveAction()), this, SLOT(onCertificateRemoveAction()));
    connect(crtList, SIGNAL(certificateExportAction()), this, SLOT(onCertificateExportAction()));
    connect(crtList, SIGNAL(certificateSignAction()), this, SLOT(onCertificateSignAction()));

    connect(ui->actionDetails, SIGNAL(triggered()), this, SLOT(onCertificateDetailsAction()));
    connect(ui->actionRemove, SIGNAL(triggered()), this, SLOT(onCertificateRemoveAction()));
    connect(ui->actionExport, SIGNAL(triggered()), this, SLOT(onCertificateExportAction()));
    connect(ui->actionSign, SIGNAL(triggered()), this, SLOT(onCertificateSignAction()));
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
    auto detail = CertificateDetailWidget::asDialog(*cert, crtMgr, this);
    detail->show();
}

void MainWindow::onCertificatesSelected(vector<Certificate *> certificates) {
    if (certificates.empty()) {
        // Disable some certificate actions in menu
        ui->actionDetails->setDisabled(true);
        ui->actionRemove->setDisabled(true);
        ui->actionExport->setDisabled(true);
        ui->actionSign->setDisabled(true);

        selectedCertificate = NULL;
    } else {
        // TODO: support multiple certificates
        selectedCertificate = certificates[0];

        ui->actionDetails->setDisabled(false);
        ui->actionRemove->setDisabled(false);
        ui->actionExport->setDisabled(false);
        ui->actionSign->setDisabled(false);
    }
}

void MainWindow::onCertificateDetailsAction() {
    if (selectedCertificate != NULL) {
        onCertificateSelected(selectedCertificate);
    }
}

void MainWindow::onCertificateRemoveAction() {
    if (selectedCertificate != NULL) {
        auto reply = QMessageBox::question(
                this,
                tr("My Application"),
                tr("You're about to remove certificate and private key.\n"
                   "Do you want to remove them?"),
                QMessageBox::Yes | QMessageBox::Abort,
                QMessageBox::Abort
        );

        if (reply != QMessageBox::Yes) {
            return;
        }

        bool success = crtMgr->removeCertifcate(selectedCertificate);

        if (success)
            crtList->showCertificates(*crtMgr->getCertificateList()->listAll());
    }

}

void MainWindow::onCertificateExportAction() {
    if (selectedCertificate != NULL) {
        ExportAssistant ea(crtMgr, selectedCertificate);
        ea.exec();
    }
}

void MainWindow::onNewCertificateAction() {
    CreateCertificateAssistant cea(crtMgr, this);

    connect(&cea, &CreateCertificateAssistant::created, this, [=](CERT_EXPORT newCert) {
        crtMgr->importNewCertificate(newCert);
        this->onCertificateImport(true);
    });

    cea.exec();
}

void MainWindow::onNewCertificateAuthorityAction() {
    CreateCACertificateAssistant caa(crtMgr, this);

    connect(&caa, &CreateCACertificateAssistant::created, this, [=](CERT_EXPORT newCert) {
        crtMgr->importNewCertificate(newCert);
        this->onCertificateImport(true);
    });

    caa.exec();
}

void MainWindow::onCertificateSignAction() {
    if (selectedCertificate != NULL) {
        SignAssistant sia(crtMgr, selectedCertificate, this);
        connect(&sia, &SignAssistant::certificateSigned, this, &MainWindow::onCertificateImport);
        sia.exec();
    }
}
