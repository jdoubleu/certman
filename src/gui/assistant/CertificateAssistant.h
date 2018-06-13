#ifndef CERTIFICATEASSISTANT_H
#define CERTIFICATEASSISTANT_H

#include <QWizard>
#include "../../cert/CertificateManager.h"
#include "../../cert/Certificate.h"

using cert::CertificateManager;
using cert::Certificate;

namespace Ui {
    class CertificateAssistant;
}

namespace gui::assistant {

    class CertificateAssistant : public QWizard {
    Q_OBJECT

    public:
        explicit CertificateAssistant(CertificateManager *crtMgr, QWidget *parent = 0);

        ~CertificateAssistant();

        void accept() override;

    private:
        Ui::CertificateAssistant *ui;

        CertificateManager *crtMgr;

        void createCertificate();

    signals:

        void created(Certificate *cert);
    };

}

#endif
