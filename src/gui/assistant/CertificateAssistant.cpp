#include "CertificateAssistant.h"
#include "ui_certificateassistant.h"
#include <QPushButton>
#include <QtWidgets/QDialogButtonBox>
#include <openssl/ossl_typ.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/x509.h>
#include <cstdlib>
#include "../../cert/Certificate.h"
#include "../../core/Environment.h"
#include <string>
#include <QStringList>
#include <QDate>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>

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
        auto to = now.addYears(v);

        ui->validityperiod_until_field->setText(
                to.toString(QLocale::system().dateFormat(QLocale::LongFormat))
        );
    };
    update_validityPeriod_until_field(ui->validityperiod_field->value());

    connect(ui->validityperiod_field, QOverload<int>::of(&QSpinBox::valueChanged), this,
            update_validityPeriod_until_field);

    //Algorithem
    ui->algorithm_field->addItem(QString("RSA"));
    ui->algorithm_field->addItem(QString("ECC"));

    auto update_algorithm_field = [=](const QString &value) {
        ui->keysize_field->clear();

        if (value.toStdString() == "RSA") {
            ui->keysize_field->addItem(QString("2048"));
            ui->keysize_field->addItem(QString("4096"));
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
    EVP_PKEY *privateKey;
    privateKey = EVP_PKEY_new();

    auto currentAlgorithm = ui->algorithm_field->currentText().toStdString();

    if (currentAlgorithm == "RSA") {
        auto keySize = ui->keysize_field->currentText().toInt();

        EVP_PKEY_CTX *ctx;
        ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);
        if (!ctx)
            /* Error occurred */
            return;

        if (EVP_PKEY_keygen_init(ctx) <= 0)
            /* Error */
            return;

        if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, keySize) <= 0)
            /* Error */
            return;
            
        /* Generate key */
        if (EVP_PKEY_keygen(ctx, &privateKey) <= 0) {
            return;
        }


    } else if (currentAlgorithm == "ECC") {

    }

    X509 *x509 = X509_new();

    //Set serialnumber to 1
    ASN1_INTEGER_set(X509_get_serialNumber(x509), 1);

    //Set valid from
    X509_gmtime_adj(X509_get_notBefore(x509), 0);

    //Set valid to
    int validityDays = ui->validityperiod_field->value();
    long validitySeconds = validityDays * 24 * 60 * 60;
    X509_gmtime_adj(X509_get_notAfter(x509), validitySeconds);

    //Set public key
    X509_set_pubkey(x509, privateKey);

    X509_NAME *name;
    name = X509_get_subject_name(x509);

    //Set name entrys
    auto cn = ui->commonName_field->text().toStdString();
    X509_NAME_add_entry_by_txt(name, SN_commonName, MBSTRING_ASC, (unsigned char *) cn.c_str(), -1, -1, 0);

    auto o = ui->organization_field->text().toStdString();
    X509_NAME_add_entry_by_txt(name, SN_organizationName, MBSTRING_ASC, (unsigned char *) o.c_str(), -1, -1, 0);

    auto ou = ui->organizationalunit_field->text().toStdString();
    X509_NAME_add_entry_by_txt(name, SN_organizationalUnitName, MBSTRING_ASC, (unsigned char *) ou.c_str(), -1, -1, 0);

    auto c = ui->countryName_field->currentText().toStdString();
    X509_NAME_add_entry_by_txt(name, SN_countryName, MBSTRING_ASC, (unsigned char *) c.c_str(), -1, -1, 0);

    auto l = ui->locality_field->text().toStdString();
    X509_NAME_add_entry_by_txt(name, SN_localityName, MBSTRING_ASC, (unsigned char *) l.c_str(), -1, -1, 0);

    auto st = ui->stateorprovince_field->text().toStdString();
    X509_NAME_add_entry_by_txt(name, SN_stateOrProvinceName, MBSTRING_ASC, (unsigned char *) st.c_str(), -1, -1, 0);

    X509_set_issuer_name(x509, name);

    //sign certificate
    X509_sign(x509, privateKey, EVP_sha1());


    //Save/export certificate and key
    auto *cert = new Certificate(x509);

    crtMgr->exportPrivateKey(privateKey, crtMgr->getPrivateKeyDefaultLocation(cert));

    crtMgr->exportCertificate(cert, crtMgr->getCertificateDefaultLocation(cert));

    //Free x509
    X509_free(x509);

    emit created(cert);

}
