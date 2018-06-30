#include <openssl/evp.h>
#include "KeyPairWidget.h"
#include "ui_keypairwidget.h"
#include "PasswordWidget.h"

using namespace gui::widget;

const SUPPORTED_KEY_ALG supportedKeyAlgorithms[] = {
    {"RSA", EVP_PKEY_RSA},
    {"DSA", EVP_PKEY_DSA},
};

const SUPPORTED_WRAPPING_ALG supportedWrappingAlgorithms[] = {
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
        ui->algorithmComboBox->addItem(tr(alg.name), QVariant(alg.algorithm));
    }
}

void KeyPairWidget::addSupportedKeyWrappingAlgorithms() {
    int row = 1;

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

void KeyPairWidget::on_wrappingAlgorithmComboBox_currentIndexChanged(int index) {
    // TODO: fix layout jumping after change
    ui->keyPassword->setHidden(index == 0);
}

bool KeyPairWidget::validate() {
    if (!ui->keyPassword->isHidden()) {

    }

    return true;
}
