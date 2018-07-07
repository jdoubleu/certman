#include "KeyUsageWidget.h"
#include "ui_keyusagewidget.h"

using namespace gui::widget;

KeyUsageWidget::KeyUsageWidget(QWidget *parent) : KeyUsageWidget(NULL, parent) {
}

KeyUsageWidget::KeyUsageWidget(CertificateManager *crtMgr, QWidget *parent) : QWidget(parent),
                                                                              ui(new Ui::KeyUsageWidget),
                                                                              crtMgr(crtMgr) {
    ui->setupUi(this);
}

KeyUsageWidget::~KeyUsageWidget() {
    delete ui;
}

void KeyUsageWidget::injectCertificateManager(CertificateManager *crtMgr) {
    this->crtMgr = crtMgr;
}

bool KeyUsageWidget::isEnabled() {
    return ui->keyusagegroup->isChecked();
}

X509_EXTENSION *KeyUsageWidget::getKeyUsageExtensions() {
    return crtMgr->generateKeyUsageExtensions(false, ui->signature_toggle->isChecked(), false, false, false,
                                              ui->key_agreement_toggle->isChecked(),
                                              ui->certificate_singing_toggle->isChecked(), false,
                                              ui->encipher_only_toggle->isChecked(),
                                              ui->decipher_only_toggle->isChecked());
}

