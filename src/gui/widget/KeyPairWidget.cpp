#include <openssl/evp.h>
#include "KeyPairWidget.h"
#include "ui_keypairwidget.h"
#include "PasswordWidget.h"

using namespace gui::widget;

const SUPPORTED_KEY_ALG supportedKeyAlgorithms[] = {
    {"RSA", EVP_PKEY_RSA, (int[]){2048, 4096}},
    {"DSA", EVP_PKEY_DSA, (int[]){2048, 3072}},
};

const SUPPORTED_WRAPPING_ALG supportedWrappingAlgorithms[] = {
    {"None", EVP_enc_null()},
    {"DES", NULL},
    {"DESede3 CBC", EVP_des_ede3_cbc()},
    {"AES", NULL},
    {"AES128 CBC", EVP_aes_128_cbc()},
    {"AES256 CBC", EVP_aes_256_cbc()},
    {"AES256 XTS", EVP_aes_256_xts()},
    {"AES256 CFB128", EVP_aes_256_xts()}
};

KeyPairWidget::KeyPairWidget(QWidget *parent): QWidget(parent), ui(new Ui::KeyPairWidget) {
    ui->setupUi(this);

    addSupportedKeyAlgorithms();
    addSupportedKeyWrappingAlgorithms();

    ui->keyPassword->setHidden(true);
}

KeyPairWidget::~KeyPairWidget() {
    delete ui;
}

void KeyPairWidget::addSupportedKeyAlgorithms() {
    for (const SUPPORTED_KEY_ALG &alg : supportedKeyAlgorithms) {
        ui->algorithmComboBox->addItem(tr(alg.name), QVariant::fromValue(alg));
    }
}

void KeyPairWidget::addSupportedKeyWrappingAlgorithms() {
    int row = 0;

    for (const SUPPORTED_WRAPPING_ALG &wrappingAlg : supportedWrappingAlgorithms) {
        QVariant data;
        if (wrappingAlg.cipher != NULL) {
            data = QVariant::fromValue(wrappingAlg);
        }

        ui->wrappingAlgorithmComboBox->addItem(tr(wrappingAlg.name), data);

        if (wrappingAlg.cipher == NULL) {
            ui->wrappingAlgorithmComboBox->setItemData(row, QVariant(0), Qt::UserRole - 1);
        }

        row++;
    }
}

void KeyPairWidget::setSupportedKeySizes(const int *sizes) {
    ui->keySizeComboBox->clear();

    for (int i = 0; i < sizeof(sizes) / sizeof(int); i++) {
        auto value = QVariant(sizes[i]);
        ui->keySizeComboBox->addItem(value.toString(), value);
    }
}

void KeyPairWidget::on_algorithmComboBox_currentIndexChanged(int index) {
    auto alg = ui->algorithmComboBox->itemData(index, Qt::UserRole).value<SUPPORTED_KEY_ALG>();
    setSupportedKeySizes(alg.keyLengths);
}

void KeyPairWidget::on_wrappingAlgorithmComboBox_currentIndexChanged(int index) {
    // TODO: fix layout jumping after change
    ui->keyPassword->setHidden(index == 0);
}

bool KeyPairWidget::validate() {
    if (!ui->keyPassword->isHidden()) {

    }

    return true;
}
