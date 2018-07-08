#ifndef PKIASSISTANT_H
#define PKIASSISTANT_H

#include <QWizard>
#include "../../cert/CertificateManager.h"

using cert::CertificateManager;
using cert::CERT_EXPORT;

namespace Ui {
    class CreateCACertificateAssistant;
}

namespace gui::assistant {

    /**
     * Represents the CA certificate assistant wizard.
     */
    class CreateCACertificateAssistant : public QWizard {
    Q_OBJECT
    public:

         /**
          * Constructor for initial wizard setup.
          * @param crtMgr Reference to certificate manager.
          * @param parent Parent widget.
          */
        explicit CreateCACertificateAssistant(CertificateManager *crtMgr, QWidget *parent = 0);

        /**
         * Destructor of the wizard.
         */
        ~CreateCACertificateAssistant();

        /**
         * Creates a CA certificate if the wizard result is successful.
         */
        void accept() override;

    private:
        /**
         * Reference to the assistant ui.
         */
        Ui::CreateCACertificateAssistant *ui;

        /**
         * Reference to the certificate manager.
         */
        CertificateManager *crtMgr;

        /**
         * Creates the CA certificate bases on the wizard content.
         */
        void createCACertificate();

    signals:
        /**
         * Inform the main window.
         * @param newCACertificate New CA certificate.
         */
        void created(CERT_EXPORT newCACertificate);
    };

}

#endif
