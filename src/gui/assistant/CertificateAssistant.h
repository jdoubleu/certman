#ifndef CERTIFICATEASSISTANT_H
#define CERTIFICATEASSISTANT_H

#include <QDialog>

namespace Ui {
    class CertificateAssistant;
}

namespace gui::assistant {

    class CertificateAssistant : public QDialog {
    Q_OBJECT

    public:
        explicit CertificateAssistant(QWidget *parent = 0);

        ~CertificateAssistant();

    private:
        Ui::CertificateAssistant *ui;

        void setupDialogButtons();
    };

}

#endif
