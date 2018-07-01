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
    connect(ui->key_choose, SIGNAL(clicked()), this, SLOT(chooseKey()));
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

    QString certPath = QFileDialog::getOpenFileName(this, tr("Choose Certificate"),
                                                    openDir,
                                                    tr("Certificate Files (*.cer *.crt *.pem *.der)"));

    if (!certPath.isEmpty()) {
        settings.setValue(IMPORT_LAST_OPEN_DIR, certPath);
    }

    QFileInfo certInfo(certPath);
    QStringList certFileName = certInfo.fileName().split('.');
    certFileName.pop_back();
    QString keyName = certFileName.join('.').append("_key.pem");

    QString keyPath = certInfo.path() + '/' + keyName;
    QFileInfo keyInfo(keyPath);

    if (keyInfo.exists() && keyInfo.isFile()) {
        ui->key_input->setText(keyPath);
    }

    ui->file_input->setText(certPath);
}

void ImportAssistant::chooseKey() {
    QSettings settings;
    QString openDir;

    if ((openDir = ui->file_input->text()).isEmpty()) {
        openDir = settings.value(IMPORT_LAST_OPEN_DIR, QString::fromStdString(Environment::getHomeDir())).toString();
    }

    QString key = QFileDialog::getOpenFileName(this, tr("Choose Key"),
                                               openDir,
                                               tr("All Files (*)"));
    ui->key_input->setText(key);
}

void ImportAssistant::submit() {
    auto fileName = ui->file_input->text();

    auto keyName = ui->key_input->text();

    crtMgr->importCertificate(fileName.toStdString(), keyName.toStdString());

    emit certificateImported(true);
}
