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

    /**
     * Structure of supported key pair algorithms.
     * E.g. RSA, DSA.
     */
    typedef struct {

        /**
         * Display name in the combo box.
         */
        const char *name;

        /**
         * Associated internal key pair algorithm.
         */
        const int algorithm = EVP_PKEY_NONE;

        /**
         * List of supported key lengths for this algorithm.
         */
        const int *keyLengths;
    } SUPPORTED_KEY_ALG;

    /**
     * Structure of a supported private key wrapping algorithm.
     * E.g. DESede3.
     */
    typedef struct {

        /**
         * Display name in the combo box.
         */
        const char *name;

        /**
         * Associated internal cipher for the private key wrapping algorithm.
         */
        const EVP_CIPHER *cipher;
    } SUPPORTED_WRAPPING_ALG;

    /**
     * KeyPairWidget class.
     */
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

        /**
         * Main constructor of the KeyPairWidget.
         * @param crtMgr reference to the CertificateManager
         * @param parent widget
         */
        explicit KeyPairWidget(CertificateManager *crtMgr, QWidget *parent);

        /**
         * Default constructor of the KeyPairWidget
         * @param parent widget
         */
        explicit KeyPairWidget(QWidget *parent);

        /**
         * KeyPairWidget destructor.
         */
        ~KeyPairWidget() override;

        /**
         * Injects the certificateManager for the keyUsageWidget.
         * @param crtMgr CertificateManager to be injected.
         */
        void injectCertificateManager(CertificateManager *crtMgr);

        /**
         * Validates the internal state.
         * @return TRUE if a valid key pair can be generated from the internal state, FALSE otherwise
         */
        bool validate();

        /**
         * Generates a key pair and prepares it for export
         * @return export structure carrying a new key pair
         */
        KEYPAIR_EXPORT generateKeyPair();

    public Q_SLOTS:

        /**
         * Slot tracking changes of algorithm combo box.
         * @param index new index
         */
        void on_algorithmComboBox_currentIndexChanged(int index);

        /**
         * Slot tracking changes of the private key wrapping algorithm.
         * @param index
         */
        void on_wrappingAlgorithmComboBox_currentIndexChanged(int index);

        /**
         * Slot tracking the algorithm's size/length combo box.
         * @param index
         */
        void on_keySizeComboBox_currentIndexChanged(int index);

        /**
         * Slot tracking changed password for some of the key wrapping algorithms.
         */
        void on_keyPassword_passwordChanged();

    Q_SIGNALS:

        /**
         * Signal indicating the internal state has changed.
         */
        void keyPairChanged();

    private:

        /**
         * Reference to the Ui factory.
         */
        Ui::KeyPairWidget *ui;

        /**
         * Reference to the CertificateManager.
         */
        CertificateManager *crtMgr;

        /**
         * Factory adding all supported algorithms to the supported key algorithms combo box.
         */
        void addSupportedKeyAlgorithms();

        /**
         * Factory adding supported key sizes of an algorithm to the combo box.
         * @param sizes
         */
        void setSupportedKeySizes(const int sizes[]);

        /**
         * Factory adding supported private key wrapping algorithms to the combo box.
         */
        void addSupportedKeyWrappingAlgorithms();
    };

};

Q_DECLARE_METATYPE(gui::widget::SUPPORTED_KEY_ALG);

Q_DECLARE_METATYPE(gui::widget::SUPPORTED_WRAPPING_ALG);

Q_DECLARE_METATYPE(cert::KEYPAIR_EXPORT);

#endif //KEYPAIRWIDGET_H
