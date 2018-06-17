#include "CertificateAssistant.h"
#include "ui_certificateassistant.h"
#include <QPushButton>
#include <QtWidgets/QDialogButtonBox>
#include "../../core/Environment.h"
#include <QDate>

using std::string;
using core::Environment;

using namespace gui::assistant;
using namespace cert;

CertificateAssistant::CertificateAssistant(CertificateManager *crtMgr, QWidget *parent) : QWizard(parent),
                                                                                          ui(new Ui::CertificateAssistant),
                                                                                          crtMgr(crtMgr) {
    ui->setupUi(this);

    // Fill country name field with iso3166 alpha2 codes
    for (string cc : Environment::iso3166_alpha2_codes_list) {
        ui->countryName_field->addItem(QString::fromStdString(cc));
    }
    ui->countryName_field->setCurrentText(QLocale::system().name().remove(0, 3));

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

    X509_NAME *name = X509_NAME_new();

    //Set name entrys
    auto cn = ui->commonName_field->text().toStdString();
    X509_NAME_add_entry_by_txt(name, SN_commonName, MBSTRING_UTF8, (unsigned char *) cn.c_str(), -1, -1, 0);

    auto o = ui->organization_field->text().toStdString();
    X509_NAME_add_entry_by_txt(name, SN_organizationName, MBSTRING_UTF8, (unsigned char *) o.c_str(), -1, -1, 0);

    auto ou = ui->organizationalunit_field->text().toStdString();
    X509_NAME_add_entry_by_txt(name, SN_organizationalUnitName, MBSTRING_UTF8, (unsigned char *) ou.c_str(), -1, -1, 0);

    auto c = ui->countryName_field->currentText().toStdString();
    X509_NAME_add_entry_by_txt(name, SN_countryName, MBSTRING_UTF8, (unsigned char *) c.c_str(), -1, -1, 0);

    auto l = ui->locality_field->text().toStdString();
    X509_NAME_add_entry_by_txt(name, SN_localityName, MBSTRING_UTF8, (unsigned char *) l.c_str(), -1, -1, 0);

    auto st = ui->stateorprovince_field->text().toStdString();
    X509_NAME_add_entry_by_txt(name, SN_stateOrProvinceName, MBSTRING_UTF8, (unsigned char *) st.c_str(), -1, -1, 0);

    bool successful = crtMgr->createCertificate(currentAlgorithm, keySize, validityDays, name, X509_NAME_dup(name));

    emit created(successful);
}
