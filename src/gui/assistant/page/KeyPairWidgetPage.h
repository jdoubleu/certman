#ifndef KEYPAIRWIDGETPAGE_H
#define KEYPAIRWIDGETPAGE_H

#include <QWizardPage>
#include "../../../cert/CertificateManager.h"

using cert::CertificateManager;

namespace Ui {
    class KeyPairWidgetPage;
}

namespace gui::assistant::page {
    class KeyPairWidgetPage : public QWizardPage {
    Q_OBJECT
    public:
        explicit KeyPairWidgetPage(QWidget *parent = 0);

        ~KeyPairWidgetPage();

        void injectCertificateManager(CertificateManager *crtMgr);

    private:
        Ui::KeyPairWidgetPage *ui;
    };
}



#endif //KEYPAIRWIDGETPAGE_H
