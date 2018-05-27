#include <QtWidgets/QFileDialog>
#include <src/core/Environment.h>
#include <QSettings>
#include "ImportAssistant.h"
#include "ui_importassistant.h"

using core::Environment;

using namespace gui::assistant;

ImportAssistant::ImportAssistant(CertificateManager *crtMgr, QWidget *parent) : QDialog(parent),
                                                                                ui(new Ui::ImportAssistant),
                                                                                crtMgr(crtMgr) {
    ui->setupUi(this);

    connect(ui->file_choose, SIGNAL(clicked()), this, SLOT(chooseFile()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(submit()));
}

ImportAssistant::~ImportAssistant() {
    delete ui;
}

void ImportAssistant::chooseFile() {
    QSettings settings;
    QString openDir;

    if ((openDir = ui->file_input->text()).isEmpty()) {
        openDir = settings.value(IMPORT_LAST_OPEN_DIR, QString::fromStdString(Environment::getHomeDir())).toString();
    }

    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose Certificate"),
                                                    openDir,
                                                    tr("Certificate Files (*.cer *.crt *.pem *.der)"));

    if (!fileName.isEmpty()) {
        settings.setValue(IMPORT_LAST_OPEN_DIR, fileName);
    }

    ui->file_input->setText(fileName);
}

void ImportAssistant::submit() {
    auto fileName = ui->file_input->text();

    crtMgr->importCertificate(fileName.toStdString());

    emit certificateImported(true);
}

