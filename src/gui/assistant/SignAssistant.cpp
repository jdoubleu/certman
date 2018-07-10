#include "SignAssistant.h"
#include "ui_signassistant.h"

using cert::CertificateContainer;
using cert::CertificateListSet;

using namespace gui::assistant;

SignAssistant::SignAssistant(CertificateManager *crtMgr, Certificate *cert, QWidget *parent) : QDialog(parent),
                                                                                               cert(cert),
                                                                                               crtMgr(crtMgr),
                                                                                               ui(new Ui::SignAssistant) {
    ui->setupUi(this);

    CertificateList *certList = crtMgr->getCertificateList();
    CertificateListSet *allCerts = certList->listAll();
    CertificateListSet::const_iterator it;


    for (it = allCerts->begin(); it != allCerts->end(); ++it) {
        Certificate *certificate = *it;
        struct CertificateContainer container = {certificate};
        ui->signing_input->addItem(QString::fromStdString(certificate->getSubjectField(LN_commonName)),
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
        bool successful = crtMgr->signCertificate(cert, signing);
        emit certificateSigned(successful);
    }
}

