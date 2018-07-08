#include "CreateCertificateAssistant.h"
#include "ui_createcertificateassistant.h"
#include <QPushButton>
#include <QtWidgets/QDialogButtonBox>
#include "../widget/NameWidget.h"
#include "../widget/KeyPairWidget.h"

using std::string;
using cert::KEYPAIR_EXPORT;
using gui::widget::NameWidget;

using namespace gui::assistant;

CreateCertificateAssistant::CreateCertificateAssistant(CertificateManager *crtMgr, QWidget *parent) : QWizard(parent),
                                                                                                      ui(new Ui::CreateCertificateAssistant),
                                                                                                      crtMgr(crtMgr) {
    ui->setupUi(this);

    ui->page_keyPair->injectCertificateManager(crtMgr);
    ui->keyUsageWidget->injectCertificateManager(crtMgr);

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

CreateCertificateAssistant::~CreateCertificateAssistant() {
    delete ui;
}

void CreateCertificateAssistant::accept() {
    createCertificate();

    QDialog::accept();
}

void CreateCertificateAssistant::createCertificate() {
    auto keyPairExport = field("keyPairWidget").value<KEYPAIR_EXPORT>();
    auto subject = field("nameWidget").value<X509_NAME *>();
    int validityDays = ui->validityperiod_field->value();
    Certificate *certificate = crtMgr->createCertificate(subject, X509_NAME_dup(subject), validityDays,
                                                         keyPairExport.keyPair);

    if (ui->keyUsageWidget->isEnabled()) {
        certificate->appendExtension(ui->keyUsageWidget->getKeyUsageExtensions());
    }

    emit created({certificate, keyPairExport});
}
