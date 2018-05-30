#include <QLabel>
#include "CertificateDetailWidget.h"
#include "ui_certificatedetail.h"

using namespace gui::widget;

CertificateDetailWidget::CertificateDetailWidget(Certificate certificate, QWidget *parent) : ui(
        new Ui::CertificateDetail), cert(certificate) {
    ui->setupUi(this);

    renderCertificate();
}

CertificateDetailWidget::~CertificateDetailWidget() {
    delete ui;
}

QDialog *CertificateDetailWidget::asDialog(Certificate certificate, QWidget *parent) {
    auto *dialog = new QDialog(parent);
    dialog->setWindowTitle(QString::fromStdString(certificate.getSubjectField("commonName")));

    auto *layout = new QGridLayout(dialog);
    layout->setMargin(10);

    layout->addWidget(new CertificateDetailWidget(certificate, dialog));

    dialog->setLayout(layout);

    return dialog;
}

void CertificateDetailWidget::renderCertificate() {
    createDetailInformationSection("Subject", cert.getSubjectFields());
    createDetailInformationSection("Issuer", cert.getIssuerFields());
}

QWidget *CertificateDetailWidget::createDetailSection(QString name) {
    auto *section = new QGroupBox(ui->certificate_details);
    section->setTitle(name);
    section->setFlat(true);

    ui->certificate_details->layout()->addWidget(section);

    return section;
}

void CertificateDetailWidget::createInformationTable(QWidget *attachTo, map<string, string> information) {
    auto table = new QFormLayout(attachTo);
    table->setMargin(0);
    table->setFormAlignment(Qt::AlignJustify | Qt::AlignTop);

    map<string, string>::iterator it;

    for (it = information.begin(); it != information.end(); it++) {
        table->addRow(
                new QLabel(QString::fromStdString(it->first), attachTo),
                new QLabel(QString::fromStdString(it->second), attachTo)
        );
    }
}

void CertificateDetailWidget::createDetailInformationSection(QString name, map<string, string> information) {
    auto *container = createDetailSection(name);
    createInformationTable(container, information);
}
