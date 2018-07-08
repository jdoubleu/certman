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

        Q_PROPERTY(cert::KEYPAIR_EXPORT keyPair
                           READ generateKeyPair
                           NOTIFY keyPairChanged
                           DESIGNABLE
                           false
                           SCRIPTABLE
                           false
                           STORED
                           false)

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

        void on_keySizeComboBox_currentIndexChanged(int index);

        void on_keyPassword_passwordChanged();

    Q_SIGNALS:

        void keyPairChanged();

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

Q_DECLARE_METATYPE(cert::KEYPAIR_EXPORT);

#endif //KEYPAIRWIDGET_H
