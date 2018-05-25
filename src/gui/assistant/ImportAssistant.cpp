#include <QtWidgets/QFileDialog>
#include <src/core/Environment.h>
#include "ImportAssistant.h"
#include "ui_importassistant.h"
#include <src/cert/CertificateManager.h>

using core::Environment;

using namespace gui::assistant;

ImportAssistant::ImportAssistant(QWidget *parent) : QDialog(parent), ui(new Ui::ImportAssistant) {
    ui->setupUi(this);

    connect(ui->file_choose, SIGNAL(clicked()), this, SLOT(chooseFile()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(submit()));
}

ImportAssistant::~ImportAssistant() {
    delete ui;
}

void ImportAssistant::chooseFile() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose Certificate"),
                                                    QString::fromStdString(Environment::getHomeDir()),
                                                    tr("Certificate Files (*.cer *.crt *.pem *.der)"));
    ui->file_input->setText(fileName);
}

void ImportAssistant::submit() {
    auto fileName = ui->file_input->text();

    auto *certManager = new cert::CertificateManager();
    certManager->importCertificate(fileName.toStdString());
}

