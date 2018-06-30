#ifndef KEYPAIRWIDGET_H
#define KEYPAIRWIDGET_H

#include <QWidget>
#include <openssl/evp.h>
#include "../../cert/CertificateManager.h"

using cert::CertificateManager;

namespace Ui {
    class KeyPairWidget;
}

namespace gui::widget {

    struct algorithmComboBox_field_st {
        const char *name;
        const int algorithm = EVP_PKEY_NONE;
        const int *keyLengths;
    };

    typedef struct algorithmComboBox_field_st SUPPORTED_KEY_ALG;

    struct wrappingAlgorithmComboBox_field_st {
        const char *name;
        const EVP_CIPHER *cipher;
    };

    typedef struct wrappingAlgorithmComboBox_field_st SUPPORTED_WRAPPING_ALG;

    class KeyPairWidget : public QWidget {
        Q_OBJECT

    public:
        explicit KeyPairWidget(CertificateManager *crtMgr, QWidget *parent);
        explicit KeyPairWidget(QWidget *parent);

        ~KeyPairWidget() override;

        void injectCertificateManager(CertificateManager *crtMgr);

        bool validate();

    public Q_SLOTS:

        void on_algorithmComboBox_currentIndexChanged(int index);
        void on_wrappingAlgorithmComboBox_currentIndexChanged(int index);

    private:

        Ui::KeyPairWidget *ui;
        CertificateManager *crtMgr;

        void addSupportedKeyAlgorithms();

        void setSupportedKeySizes(const int sizes[]);

        void addSupportedKeyWrappingAlgorithms();
    };

};

Q_DECLARE_METATYPE(gui::widget::SUPPORTED_KEY_ALG);
Q_DECLARE_METATYPE(gui::widget::SUPPORTED_WRAPPING_ALG);

#endif //KEYPAIRWIDGET_H
