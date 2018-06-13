#include "CertificateAssistant.h"
#include "ui_certificateassistant.h"
#include "../../core/Environment.h"
#include <string>
#include <QStringList>
#include <iostream>

using std::string;
using std::cout;
using core::Environment;

using namespace gui::assistant;

CertificateAssistant::CertificateAssistant(QWidget *parent) : QWizard(parent),
                                                              ui(new Ui::CertificateAssistant) {
    ui->setupUi(this);

    // Fill country name field with iso3166 alpha2 codes
    for (string cc : Environment::iso3166_alpha2_codes_list) {
        ui->countryName_field->addItem(QString::fromStdString(cc));
    }
    ui->countryName_field->setCurrentText(QLocale::system().name().remove(0, 3));
}

CertificateAssistant::~CertificateAssistant() {
    delete ui;
}

void CertificateAssistant::accept() {
    QDialog::accept();
}
