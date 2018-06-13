#ifndef CERTIFICATEASSISTANT_H
#define CERTIFICATEASSISTANT_H

#include <QDialog>
#include <src/cert/CertificateManager.h>
#include "../../cert/Certificate.h"

using cert::CertificateManager;

namespace Ui {
    class CertificateAssistant;
}

namespace gui::assistant {

    class CertificateAssistant : public QDialog {
    Q_OBJECT

    public:
        explicit CertificateAssistant(CertificateManager *crtMgr, QWidget *parent = 0);

        ~CertificateAssistant();

    private:
        Ui::CertificateAssistant *ui;

        CertificateManager *crtMgr;

        void setupDialogButtons();

        void createCertificate();
    };

}

#endif
