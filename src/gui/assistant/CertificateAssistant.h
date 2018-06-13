#ifndef CERTIFICATEASSISTANT_H
#define CERTIFICATEASSISTANT_H

<<<<<<< HEAD
#include <QDialog>
#include <src/cert/CertificateManager.h>
#include "../../cert/Certificate.h"

using cert::CertificateManager;
=======
#include <QWizard>
#include "../../cert/Certificate.h"

using cert::Certificate;
>>>>>>> 11-create-certificate

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

        void setupDialogButtons();

<<<<<<< HEAD
        void createCertificate();
=======
    signals:

        void created(Certificate *cert);
>>>>>>> 11-create-certificate
    };

}

#endif
