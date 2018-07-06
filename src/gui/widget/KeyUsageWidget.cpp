#include "KeyUsageWidget.h"
#include "ui_keyusagewidget.h"

using namespace gui::widget;

KeyUsageWidget::KeyUsageWidget(QWidget *parent) : QWidget(parent), ui(new Ui::KeyUsageWidget) {
    ui->setupUi(this);
}

KeyUsageWidget::~KeyUsageWidget() {
    delete ui;
}

bool KeyUsageWidget::isEnabled() {
    return ui->keyusagegroup->isChecked();
}

X509_EXTENSION *KeyUsageWidget::getKeyUsageExtensions() {
    ASN1_BIT_STRING *keyUsage = ASN1_BIT_STRING_new();
    ASN1_BIT_STRING_set_bit(keyUsage, 0, ui->signature_toggle->isChecked());
    ASN1_BIT_STRING_set_bit(keyUsage, 1, false);
    ASN1_BIT_STRING_set_bit(keyUsage, 2, false);
    ASN1_BIT_STRING_set_bit(keyUsage, 3, false);
    ASN1_BIT_STRING_set_bit(keyUsage, 4, ui->key_agreement_toggle->isChecked());
    ASN1_BIT_STRING_set_bit(keyUsage, 5, ui->certificate_singing_toggle->isChecked());
    ASN1_BIT_STRING_set_bit(keyUsage, 6, false);
    ASN1_BIT_STRING_set_bit(keyUsage, 7, ui->encipher_only_toggle->isChecked());
    ASN1_BIT_STRING_set_bit(keyUsage, 8, ui->decipher_only_toggle->isChecked());

    unsigned char *buf = NULL;
    int len = i2d_ASN1_BIT_STRING(keyUsage, &buf);
    ASN1_OCTET_STRING *data = ASN1_OCTET_STRING_new();
    ASN1_OCTET_STRING_set(data, buf, len);

    X509_EXTENSION *ext = X509_EXTENSION_create_by_NID(NULL, NID_key_usage, false, data);
    return ext;
}

