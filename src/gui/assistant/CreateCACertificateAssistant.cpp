#include "CreateCACertificateAssistant.h"
#include "ui_createcacertificateassistant.h"

using gui::widget::NameWidget;
using cert::KEYPAIR_EXPORT;
using cert::Certificate;

using namespace gui::assistant;

CreateCACertificateAssistant::CreateCACertificateAssistant(CertificateManager *crtMgr, QWidget *parent) : QWizard(
        parent), ui(new Ui::CreateCACertificateAssistant), crtMgr(crtMgr) {
    ui->setupUi(this);

    ui->keyPairWidget->injectCertificateManager(crtMgr);

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
}

CreateCACertificateAssistant::~CreateCACertificateAssistant() {
    delete ui;
}

void CreateCACertificateAssistant::accept() {
    createCACertificate();

    QDialog::accept();
}

void CreateCACertificateAssistant::createCACertificate() {
    KEYPAIR_EXPORT keyPairExport = ui->keyPairWidget->generateKeyPair();
    X509_NAME *subject = ui->nameWidget->getX509Name();
    int validityDays = ui->validityperiod_field->value();
    int pathLen = ui->pathLengthSpinBox->value();

    Certificate *ca = crtMgr->createCertificate(subject, X509_NAME_dup(subject), validityDays, keyPairExport.keyPair);
    ca->addBasicConstraints(true, pathLen);
    auto *ext = crtMgr->generateKeyUsageExtensions(true, true, false, false, false, false, true);
    ca->appendExtension(ext);

    emit created({
                         ca,
                         keyPairExport
                 });
}
