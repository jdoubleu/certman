#include "SignAssistant.h"
#include "ui_signassistant.h"

using cert::CertificateContainer;

using namespace gui::assistant;

SignAssistant::SignAssistant(CertificateManager *crtMgr, Certificate *cert, QWidget *parent) : QDialog(parent),
                                                                                               cert(cert),
                                                                                               crtMgr(crtMgr),
                                                                                               ui(new Ui::SignAssistant) {
    ui->setupUi(this);

    CertificateList *certList = crtMgr->getCertificateList();
    unordered_set<Certificate *, CertificateList::CertificateHashByThumbprint, CertificateList::CertificateEqualByThumbprint> *allCerts = certList->listAll();
    unordered_set<Certificate *, CertificateList::CertificateHashByThumbprint, CertificateList::CertificateEqualByThumbprint>::const_iterator it;


    for (it = allCerts->begin(); it != allCerts->end(); ++it) {
        Certificate *certifcate = *it;
        struct CertificateContainer container = {certifcate};
        ui->signing_input->addItem(QString::fromStdString(certifcate->getSubjectField(LN_commonName)),
                                   QVariant::fromValue(container));
    }

    string cn = cert->getSubjectField(LN_commonName);
    ui->sign_certificate->setText(QString::fromStdString(cn));

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(submit()));
}

SignAssistant::~SignAssistant() {
    delete ui;
}

void SignAssistant::submit() {
    auto signing = ui->signing_input->currentData(Qt::UserRole).value<CertificateContainer>().certificate;
    bool hasKey = crtMgr->hasPrivateKey(signing);
    if (hasKey) {

        //Get signing key
        EVP_PKEY *pKey = crtMgr->getKey(crtMgr->getPrivateKeyDefaultLocation(signing));
        X509_NAME *parentSubject = X509_get_subject_name(signing->getX509());
        bool successful = crtMgr->signCertificate(cert, pKey, parentSubject);
        emit certificateSigned(successful);
    }
}

