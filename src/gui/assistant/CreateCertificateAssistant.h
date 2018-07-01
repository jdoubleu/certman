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
    class CertificateAssistant;
}

namespace gui::assistant {

    class CreateCertificateAssistant : public QWizard {
    Q_OBJECT

    public:
        explicit CreateCertificateAssistant(CertificateManager *crtMgr, QWidget *parent = 0);

        ~CreateCertificateAssistant();

        void accept() override;

    private:
        Ui::CertificateAssistant *ui;

        CertificateManager *crtMgr;

        void createCertificate();

    signals:

        void created(CERT_EXPORT newCertificate);
    };

}

#endif
