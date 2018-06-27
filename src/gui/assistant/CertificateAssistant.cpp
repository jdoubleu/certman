#include "CertificateAssistant.h"
#include "ui_certificateassistant.h"
#include <QPushButton>
#include <QtWidgets/QDialogButtonBox>

using std::string;
using gui::widget::NameWidget;

using namespace gui::assistant;
using namespace cert;

CertificateAssistant::CertificateAssistant(CertificateManager *crtMgr, QWidget *parent) : QWizard(parent),
                                                                                          ui(new Ui::CertificateAssistant),
                                                                                          crtMgr(crtMgr) {
    ui->setupUi(this);

    // validity
    auto now = QDate::currentDate();
    ui->validityperiod_from_field->setText(
            now.toString(QLocale::system().dateFormat(QLocale::LongFormat))
    );

    auto update_validityPeriod_until_field = [=](int v) {
        auto to = now.addDays(v);

        ui->validityperiod_until_field->setText(
                to.toString(QLocale::system().dateFormat(QLocale::LongFormat))
        );
    };
    update_validityPeriod_until_field(ui->validityperiod_field->value());

    connect(ui->validityperiod_field, QOverload<int>::of(&QSpinBox::valueChanged), this,
            update_validityPeriod_until_field);

    //Algorithem
    ui->algorithm_field->addItem(QString(SN_rsa), EVP_PKEY_RSA);
    //ui->algorithm_field->addItem(QString("ECC"), EVP_PKEY_EC);
    ui->algorithm_field->addItem(QString(SN_dsa), EVP_PKEY_DSA);

    auto update_algorithm_field = [=](const QString &value) {
        ui->keysize_field->clear();

        if (value.toStdString() == SN_rsa) {
            ui->keysize_field->addItem(QString("2048"));
            ui->keysize_field->addItem(QString("4096"));
        } else if (value.toStdString() == SN_dsa) {
            ui->keysize_field->addItem(QString("1024"));
            ui->keysize_field->addItem(QString("2048"));
        }
    };
    update_algorithm_field(ui->algorithm_field->currentText());

    connect(ui->algorithm_field, QOverload<const QString &>::of(&QComboBox::currentIndexChanged), this,
            update_algorithm_field);
}

CertificateAssistant::~CertificateAssistant() {
    delete ui;
}

void CertificateAssistant::accept() {
    createCertificate();

    QDialog::accept();
}

void CertificateAssistant::createCertificate() {
    auto currentAlgorithm = ui->algorithm_field->currentData().toInt();
    auto keySize = ui->keysize_field->currentText().toInt();
    int validityDays = ui->validityperiod_field->value();

    auto *name = ui->subject_name->getX509Name();

    bool successful = crtMgr->createCertificate(currentAlgorithm, keySize, validityDays, name, X509_NAME_dup(name));

    emit created(successful);
}
