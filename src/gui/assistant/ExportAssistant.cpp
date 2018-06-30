#include <QtWidgets/QFileDialog>
#include <src/core/Environment.h>
#include <QSettings>
#include <iostream>
#include "ExportAssistant.h"
#include "ui_exportassistant.h"

using core::Environment;

using namespace gui::assistant;

ExportAssistant::ExportAssistant(CertificateManager *crtMgr, Certificate *cert, QWidget *parent) : QDialog(parent),
                                                                                                   ui(new Ui::ExportAssistant),
                                                                                                   crtMgr(crtMgr),
                                                                                                   cert(cert) {
    ui->setupUi(this);

    string cn = cert->getSubjectField(LN_commonName);
    if(!cn.empty()) {
        QString openDir;
        QSettings settings;
        openDir = settings.value(EXPORT_LAST_OPEN_DIR, QString::fromStdString(Environment::getHomeDir())).toString();

        cn.erase(std::remove(cn.begin(), cn.end(), '*'), cn.end());
        std::replace(cn.begin(), cn.end(), '.', '_');

        QFileInfo original(openDir);
        QString newPath = original.canonicalPath() + QDir::separator() + QString::fromStdString(cn);
        if (!original.completeSuffix().isEmpty())
            newPath += "." + original.completeSuffix();

        QString newPathKey = original.canonicalPath() + QDir::separator() + QString::fromStdString(cn) +
                             QString::fromStdString("_key.pem");

        ui->file_input->setText(newPath);

        if (!crtMgr->hasPrivateKey(cert)) {
            ui->widget_location_key->hide();
        } else {
            ui->key_input->setText(newPathKey);
        }
    }

    connect(ui->file_choose, SIGNAL(clicked()), this, SLOT(chooseFile()));
    connect(ui->key_choose, SIGNAL(clicked()), this, SLOT(chooseKey()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(submit()));
}

ExportAssistant::~ExportAssistant() {
    delete ui;
}

void ExportAssistant::chooseFile() {
    QSettings settings;
    QString openDir;

    if ((openDir = ui->file_input->text()).isEmpty()) {
        openDir = settings.value(EXPORT_LAST_OPEN_DIR, QString::fromStdString(Environment::getHomeDir())).toString();
    }

    QString certPath = QFileDialog::getSaveFileName(this, tr("Choose Certificate"),
                                                    openDir,
                                                    tr("Certificate Files (*.cer *.crt *.pem *.der)"));

    if (!certPath.isEmpty()) {
        settings.setValue(EXPORT_LAST_OPEN_DIR, certPath);
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

void ExportAssistant::chooseKey() {
    QSettings settings;
    QString openDir;

    if ((openDir = ui->file_input->text()).isEmpty()) {
        openDir = settings.value(EXPORT_LAST_OPEN_DIR, QString::fromStdString(Environment::getHomeDir())).toString();
    }

    QString key = QFileDialog::getSaveFileName(this, tr("Choose Key"),
                                               openDir,
                                               tr("Certificate Files (*.pem *.der)"));
    ui->key_input->setText(key);
}

void ExportAssistant::submit() {
    auto fileName = ui->file_input->text();

    auto keyName = ui->key_input->text();

    if (fileName != NULL) {
        crtMgr->exportCertificate(cert, fileName.toStdString());
    }

    if (keyName != NULL) {
        crtMgr->exportPrivateKeyFile(crtMgr->getPrivateKeyDefaultLocation(cert), keyName.toStdString());
    }

    emit certificateExported(true);
}
