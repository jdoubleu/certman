#ifndef SIGNASSISTANT_H
#define SIGNASSISTANT_H

#include <QDialog>
#include <src/cert/Certificate.h>
#include "../../cert/CertificateManager.h"
#include "../../cert/CertificateList.h"

using cert::Certificate;
using cert::CertificateManager;
using cert::CertificateList;

namespace Ui {
    class SignAssistant;
}

namespace gui::assistant {

    class SignAssistant : public QDialog {
    Q_OBJECT

    public:
        explicit SignAssistant(CertificateManager *crtMgr, Certificate *cert, QWidget *parent);

        ~SignAssistant();

    private:
        Ui::SignAssistant *ui;
        Certificate *cert;
        CertificateManager *crtMgr;

    private slots:

        void submit();

    signals:

        void certificateSigned(bool successful);

    };
}
#endif
