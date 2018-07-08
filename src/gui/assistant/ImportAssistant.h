#ifndef IMPORTASSISTANT_H
#define IMPORTASSISTANT_H

#include <QDialog>
#include "../../cert/CertificateManager.h"

using cert::CertificateManager;

namespace Ui {
    class ImportAssistant;
}

namespace gui::assistant {

    /**
     * Key for storing last opened dir with importer.
     */
    const QString IMPORT_LAST_OPEN_DIR("import_open_dir");

    /**
     * Represent the import assistant.
     */
    class ImportAssistant : public QDialog {
    Q_OBJECT

    public:
        /**
         * Constructor for assistant dialog.
         * @param crtMgr Reference to the certificate Manager.
         * @param parent Parent to widget.
         */
        explicit ImportAssistant(CertificateManager *crtMgr, QWidget *parent = 0);

        /**
         * Destructs the ui.
         */
        ~ImportAssistant();

    private:
        /**
         * Reference to the ui.
         */
        Ui::ImportAssistant *ui;

        /**
         * Reference to the certificate manager.
         */
        CertificateManager *crtMgr;

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
        void certificateImported(bool successful);
    };

}

#endif
