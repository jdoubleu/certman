#ifndef EXPORTASSISTANT_H
#define EXPORTASSISTANT_H

#include <QDialog>
#include "../../cert/CertificateManager.h"
#include "../../cert/Certificate.h"

using cert::CertificateManager;
using cert::Certificate;

namespace Ui {
    class ExportAssistant;
}

namespace gui::assistant {

    /**
     * Key for storing last opened dir with exporter
     */
    const QString EXPORT_LAST_OPEN_DIR("export_open_dir");

    /**
     * Represent the export assistant.
     */
    class ExportAssistant : public QDialog {
    Q_OBJECT

    public:
        /**
         * Constructor of the assistant.
         * @param crtMgr Reference to the certificate manager.
         * @param cert Certificate to be exported.
         * @param parent Parent widget.
         */
        explicit ExportAssistant(CertificateManager *crtMgr, Certificate *cert, QWidget *parent = 0);

        /**
         * Destructs the ui.
         */
        ~ExportAssistant();

    private:
        /**
         * Reference to the ui.
         */
        Ui::ExportAssistant *ui;

        /**
         * Reference to the certificate manager.
         */
        CertificateManager *crtMgr;

        /**
         * Reference to the exportable certificate.
         */
        Certificate *cert;

    private slots:

        /**
         * Action after certificate file is chosen.
         */
        void chooseFile();

        /**
         * Action after certificate key file is chosen.
         */
        void chooseKey();

        /**
         * Action on wizard submission.
         */
        void submit();

    signals:

        /**
         * Informs the main window of the dialog result.
         * @param successful Result of the dialog.
         */
        void certificateExported(bool successful);
    };

}

#endif
