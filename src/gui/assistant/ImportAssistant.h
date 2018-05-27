#include <QDialog>
#include "../../cert/CertificateManager.h"

using cert::CertificateManager;

namespace Ui {
    class ImportAssistant;
}

namespace gui::assistant {

    class ImportAssistant : public QDialog {
    Q_OBJECT

    public:
        explicit ImportAssistant(CertificateManager *crtMgr, QWidget *parent = 0);

        ~ImportAssistant();

    private:
        Ui::ImportAssistant *ui;

        CertificateManager *crtMgr;

    private slots:

        void chooseFile();

        void submit();
    };

}
