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

    class CreateCACertificateAssistant : public QWizard {
    Q_OBJECT
    public:
        explicit CreateCACertificateAssistant(CertificateManager *crtMgr, QWidget *parent = 0);

        ~CreateCACertificateAssistant();

        void accept() override ;

    private:
        Ui::CreateCACertificateAssistant *ui;

        CertificateManager *crtMgr;

        void createCACertificate();

    signals:

        void created(CERT_EXPORT newCACertificate);
    };

}

#endif
