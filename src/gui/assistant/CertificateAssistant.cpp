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

using namespace gui::assistant;
using namespace cert;

CertificateAssistant::CertificateAssistant(CertificateManager *crtMgr, QWidget *parent) : QDialog(parent),
                                                              ui(new Ui::CertificateAssistant),
                                                              crtMgr(crtMgr){
    ui->setupUi(this);

    setupDialogButtons();
}

CertificateAssistant::~CertificateAssistant() {
    delete ui;
}

void CertificateAssistant::setupDialogButtons() {
    auto nextButton = new QPushButton(tr("Continue"));
    nextButton->setDefault(true);

    auto previousButton = new QPushButton(tr("Back"));

    ui->dialog_buttons->addButton(nextButton, QDialogButtonBox::ApplyRole);
    ui->dialog_buttons->addButton(previousButton, QDialogButtonBox::ResetRole);

    connect(nextButton, &QAbstractButton::clicked, this, [=] {
        int current = ui->pages_widget->currentIndex();

        ui->pages_widget->setCurrentIndex(current + 1);
    });

    connect(previousButton, &QAbstractButton::clicked, this, [=] {
        int current = ui->pages_widget->currentIndex();

        ui->pages_widget->setCurrentIndex(current - 1);
    });
}

void CertificateAssistant::createCertificate() {
    EVP_PKEY *pkey;
    pkey = EVP_PKEY_new();

    auto currentAlgorithm = ui->algorithm_field->currentText().toStdString();

    if(currentAlgorithm == "RSA") {
        auto keySize = ui->keysize_field->currentText().toInt();


        //Generate key
        RSA *rsa;
        BIGNUM *bne = BN_new();
        int ret = 0;
        unsigned long e = RSA_F4;

        BN_set_word(bne,e);
        srand ( time(NULL) );
        ret = RSA_generate_key_ex(rsa, keySize,bne,NULL);
        if(ret != 1) {
            RSA_free(rsa);
            BN_free(bne);
        }

        EVP_PKEY_assign_RSA(pkey, rsa);
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
    X509_set_pubkey(x509, pkey);

    X509_NAME *name;
    name = X509_get_subject_name(x509);

    //Set name entrys
    auto cn = ui->commonName_field->text().toStdString();
    X509_NAME_add_entry_by_txt(name, "CN", MBSTRING_ASC, (unsigned char *)cn.c_str(), -1, -1, 0);

    auto o = ui->organization_field->text().toStdString();
    X509_NAME_add_entry_by_txt(name, "O", MBSTRING_ASC, (unsigned char *)o.c_str(), -1, -1, 0);

    auto ou = ui->organizationalunit_field->text().toStdString();
    X509_NAME_add_entry_by_txt(name, "OU", MBSTRING_ASC, (unsigned char *)ou.c_str(), -1, -1, 0);

    auto c = ui->countryName_field->currentText().toStdString();
    X509_NAME_add_entry_by_txt(name, "C", MBSTRING_ASC, (unsigned char *)c.c_str(), -1, -1, 0);

    auto l = ui->locality_field->text().toStdString();
    X509_NAME_add_entry_by_txt(name, "L", MBSTRING_ASC, (unsigned char *)l.c_str(), -1, -1, 0);

    auto st = ui->stateorprovince_field->text().toStdString();
    X509_NAME_add_entry_by_txt(name, "ST", MBSTRING_ASC, (unsigned char *)st.c_str(), -1, -1, 0);

    auto mail = ui->emailAddress_field->text().toStdString();
    X509_NAME_add_entry_by_txt(name, "emailAddress", MBSTRING_ASC, (unsigned char *)mail.c_str(), -1, -1, 0);

    X509_set_issuer_name(x509, name);

    //sign certificate
    X509_sign(x509, pkey, EVP_sha1());


    //Save/export certificate and key
    auto *cert = new Certificate(x509);

    crtMgr->exportPrivateKey(pkey,crtMgr->getPrivateKeyDefaultLocation(cert));

    crtMgr->exportCertificate(cert, crtMgr->getCertificateDefaultLocation(cert));

    //Free x509
    X509_free(x509);

}
