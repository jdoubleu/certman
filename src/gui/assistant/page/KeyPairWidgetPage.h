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

        bool isComplete() const override;

    public Q_SLOTS:

        void on_keyPairWidget_keyPairChanged();

    private:
        Ui::KeyPairWidgetPage *ui;
    };
}



#endif //KEYPAIRWIDGETPAGE_H
