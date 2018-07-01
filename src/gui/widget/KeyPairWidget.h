#ifndef KEYPAIRWIDGET_H
#define KEYPAIRWIDGET_H

#include <QWidget>
#include <openssl/evp.h>
#include "../../cert/CertificateManager.h"

using cert::CertificateManager;
using cert::KEYPAIR_EXPORT;

namespace Ui {
    class KeyPairWidget;
}

namespace gui::widget {

    typedef struct {
        const char *name;
        const int algorithm = EVP_PKEY_NONE;
        const int *keyLengths;
    } SUPPORTED_KEY_ALG;

    typedef struct {
        const char *name;
        const EVP_CIPHER *cipher;
    } SUPPORTED_WRAPPING_ALG;

    class KeyPairWidget : public QWidget {
    Q_OBJECT

    public:
        explicit KeyPairWidget(CertificateManager *crtMgr, QWidget *parent);

        explicit KeyPairWidget(QWidget *parent);

        ~KeyPairWidget() override;

        void injectCertificateManager(CertificateManager *crtMgr);

        bool validate();

        KEYPAIR_EXPORT generateKeyPair();

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
