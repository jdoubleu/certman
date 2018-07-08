#ifndef CERTIFICATEASSISTANT_H
#define CERTIFICATEASSISTANT_H

#include <QWizard>
#include "../../cert/CertificateManager.h"
#include "../../cert/Certificate.h"
#include "../widget/KeyPairWidget.h"

using cert::CertificateManager;
using cert::Certificate;
using cert::CERT_EXPORT;

namespace Ui {
    class CreateCertificateAssistant;
}

namespace gui::assistant {

    /**
     * Represents the certificate assistant wizard.
     */
    class CreateCertificateAssistant : public QWizard {
    Q_OBJECT

    public:
        /**
          * Constructor for initial wizard setup.
          * @param crtMgr Reference to certificate manager.
          * @param parent Parent widget.
          */
        explicit CreateCertificateAssistant(CertificateManager *crtMgr, QWidget *parent = 0);

        /**
         * Destructs the wizard ui.
         */
        ~CreateCertificateAssistant();

        /**
         * Creates a certificate if the wizard result is successful.
         */
        void accept() override;

    private:
        /**
         * Reference to the assistant ui.
         */
        Ui::CreateCertificateAssistant *ui;

        /**
         * Reference to the certificate manager.
         */
        CertificateManager *crtMgr;

        /**
        * Creates the certificate based on the wizard content.
        */
        void createCertificate();

    signals:
        /**
         * Inform the main window.
         * @param newCertificate New certificate.
         */
        void created(CERT_EXPORT newCertificate);
    };

}

#endif
