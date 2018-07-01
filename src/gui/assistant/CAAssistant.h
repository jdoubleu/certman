#ifndef PKIASSISTANT_H
#define PKIASSISTANT_H

#include <QWizard>
#include "../../cert/CertificateManager.h"

using cert::CertificateManager;
using cert::CERT_EXPORT;

namespace Ui {
    class CAAssistant;
}

namespace gui::assistant {

    class CAAssistant : public QWizard {
    Q_OBJECT
    public:
        explicit CAAssistant(CertificateManager *crtMgr, QWidget *parent = 0);

        ~CAAssistant();

        void accept() override ;

    private:
        Ui::CAAssistant *ui;

        CertificateManager *crtMgr;

        void createCACertificate();

    signals:

        void created(CERT_EXPORT newCACertificate);
    };

}

#endif
