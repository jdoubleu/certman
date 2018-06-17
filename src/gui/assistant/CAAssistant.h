#ifndef PKIASSISTANT_H
#define PKIASSISTANT_H

#include <QWizard>
#include "../../cert/CertificateManager.h"

using cert::CertificateManager;

namespace Ui {
    class CAAssistant;
}

namespace gui::assistant {

    class CAAssistant : public QWizard {
    Q_OBJECT
    public:
        explicit CAAssistant(CertificateManager *crtMgr, QWidget *parent = 0);

        ~CAAssistant();

    private:
        Ui::CAAssistant *ui;
        CertificateManager *crtMgr;
    };

}

#endif
