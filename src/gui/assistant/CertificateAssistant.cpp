#include "CertificateAssistant.h"
#include "ui_certificateassistant.h"
#include <QPushButton>
#include <QtWidgets/QDialogButtonBox>
#include <QDate>
#include "../widget/KeyPairWidget.h"
#include "../widget/NameWidget.h"

using std::string;
using gui::widget::NameWidget;
using cert::KEYPAIR_EXPORT;

using namespace gui::assistant;

CertificateAssistant::CertificateAssistant(CertificateManager *crtMgr, QWidget *parent) : QWizard(parent),
                                                                                          ui(new Ui::CertificateAssistant),
                                                                                          crtMgr(crtMgr) {
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

CertificateAssistant::~CertificateAssistant() {
    delete ui;
}

void CertificateAssistant::accept() {
    createCertificate();

    QDialog::accept();
}

void CertificateAssistant::createCertificate() {
    KEYPAIR_EXPORT keyPairExport = ui->keyPairWidget->generateKeyPair();
    X509_NAME *subject = ui->subject_name->getX509Name();
    int validityDays = ui->validityperiod_field->value();
    Certificate *certificate = crtMgr->createCertificate(subject, X509_NAME_dup(subject), validityDays, keyPairExport.keyPair);

    emit created({
            certificate,
            keyPairExport
    });
}
