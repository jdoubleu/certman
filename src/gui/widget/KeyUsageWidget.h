#ifndef KEYUSAGEWIDGET_H
#define KEYUSAGEWIDGET_H

#include <QWidget>
#include <openssl/x509v3.h>
#include "../../cert/CertificateManager.h"

using cert::CertificateManager;

namespace Ui {
    class KeyUsageWidget;
}

namespace gui::widget {

    /**
     * Class represents a widget to configure key usage.
     */
    class KeyUsageWidget : public QWidget {
    Q_OBJECT

    public:

        /**
         * Constructor for a keyUsageWidget.
         * @param crtMgr CertificateManager to generate extensions.
         * @param parent Parent widget element.
         */
        explicit KeyUsageWidget(CertificateManager *crtMgr, QWidget *parent);

        /**
         * Constructor for a keyUsageWidget.
         * @param parent Parent widget element.
         */
        explicit KeyUsageWidget(QWidget *parent);

        /**
         * Destructor for a keyUsageWidget.
         */
        ~KeyUsageWidget();

        /**
         * Check if the keyUsageExtension is enabled.
         * @return Boolean if keyUsage is enabled.
         */
        bool isEnabled();

        /**
         * Gets the extension for the keyUsage.
         * @return X509_EXTENSION for the keyUsage.
         */
        X509_EXTENSION *getKeyUsageExtensions();

        /**
         * Injects the certificateManager for the keyUsageWidget.
         * @param crtMgr CertificateManager to be injected.
         */
        void injectCertificateManager(CertificateManager *crtMgr);

    private:

        /**
         * Ui element of keyUsageWidget.
         */
        Ui::KeyUsageWidget *ui;

        /**
         * CertificateManager to generate extensions.
         */
        CertificateManager *crtMgr;

    };
}


#endif
