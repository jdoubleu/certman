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

    class ExportAssistant : public QDialog {
    Q_OBJECT

    public:
        explicit ExportAssistant(CertificateManager *crtMgr, Certificate *cert, QWidget *parent = 0);

        ~ExportAssistant();

    private:
        Ui::ExportAssistant *ui;

        CertificateManager *crtMgr;

        Certificate *cert;

    private slots:

        void chooseFile();

        void chooseKey();

        void submit();

    signals:

        void certificateExported(bool successful);
    };

}

#endif
