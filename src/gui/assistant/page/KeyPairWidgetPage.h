#ifndef KEYPAIRWIDGETPAGE_H
#define KEYPAIRWIDGETPAGE_H

#include <QWizardPage>
#include "../../../cert/CertificateManager.h"

using cert::CertificateManager;

namespace Ui {
    class KeyPairWidgetPage;
}

namespace gui::assistant::page {

    /**
     * Represents the key pair wizard page.
     */
    class KeyPairWidgetPage : public QWizardPage {
    Q_OBJECT
    public:
        /**
         * Constructor for the wizard page.
         * @param parent Reference to the parent widget.
         */
        explicit KeyPairWidgetPage(QWidget *parent = 0);

        /**
         * Destructor for the wizard page.
         */
        ~KeyPairWidgetPage();

        /**
         * Injects the certificate manager.
         * @param crtMgr Reference to the certificate manager.
         */
        void injectCertificateManager(CertificateManager *crtMgr);

        /**
         * Checks if the wizard page is valid.
         * @return Return true if the wizard page completed.
         */
        bool isComplete() const override;

    public Q_SLOTS:
        /**
         * Handles the changed event.
         */
        void on_keyPairWidget_keyPairChanged();

    private:
        /**
         * Reference to the ui page.
         */
        Ui::KeyPairWidgetPage *ui;
    };
}



#endif //KEYPAIRWIDGETPAGE_H
