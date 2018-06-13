#ifndef CERTIFICATEASSISTANT_H
#define CERTIFICATEASSISTANT_H

#include <QWizard>
#include "../../cert/Certificate.h"

using cert::Certificate;

namespace Ui {
    class CertificateAssistant;
}

namespace gui::assistant {

    class CertificateAssistant : public QWizard {
    Q_OBJECT

    public:
        explicit CertificateAssistant(QWidget *parent = 0);

        ~CertificateAssistant();

        void accept() override;

    private:
        Ui::CertificateAssistant *ui;

        void setupDialogButtons();

    signals:

        void created(Certificate *cert);
    };

}

#endif
