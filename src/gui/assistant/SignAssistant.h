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

    /**
     * Represents the dialog for certificate signing.
     */
    class SignAssistant : public QDialog {
    Q_OBJECT

    public:
        /**
         * Constructor for dialog.
         * @param crtMgr Certificate manger.
         * @param cert Certificate to be signed.
         * @param parent Parent widget.
         */
        explicit SignAssistant(CertificateManager *crtMgr, Certificate *cert, QWidget *parent);

        /**
         * Cleanup the ui dialog.
         */
        ~SignAssistant();

    private:
        /**
         * Reference to the assistant ui.
         */
        Ui::SignAssistant *ui;

        /**
         * Certificate to be signed.
         */
        Certificate *cert;

        /**
         * Reference to certificate manager.
         */
        CertificateManager *crtMgr;

    private slots:
        /**
         * Dialog submit action.
         */
        void submit();

    signals:
        /**
         * Informs the main window of the dialog result.
         * @param successful Result of the dialog.
         */
        void certificateSigned(bool successful);

    };
}
#endif
