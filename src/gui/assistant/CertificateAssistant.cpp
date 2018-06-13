#include "CertificateAssistant.h"
#include "ui_certificateassistant.h"

using namespace gui::assistant;

CertificateAssistant::CertificateAssistant(QWidget *parent) : QWizard(parent),
                                                              ui(new Ui::CertificateAssistant) {
    ui->setupUi(this);
}

CertificateAssistant::~CertificateAssistant() {
    delete ui;
}

void CertificateAssistant::accept() {
    QDialog::accept();
}
