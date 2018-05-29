#ifndef CERTIFICATEDETAILWIDGET_H
#define CERTIFICATEDETAILWIDGET_H

#include <QWidget>
#include <QFormLayout>
#include <QGroupBox>
#include <QDialog>
#include "../../cert/Certificate.h"

using cert::Certificate;

namespace Ui {
    class CertificateDetail;
}

namespace gui::widget {

    class CertificateDetailWidget : public QWidget {
    Q_OBJECT
    public:
        explicit CertificateDetailWidget(Certificate certificate, QWidget *parent = 0);

        ~CertificateDetailWidget();

        static QDialog *asDialog(Certificate certificate, QWidget *parent = 0);

    private:
        Ui::CertificateDetail *ui;
        Certificate cert;

        void renderCertificate();

        QWidget *createDetailSection(QString name);

        void createInformationTable(QWidget *attachTo, map<string, string> information);

        void createDetailInformationSection(QString name, map<string, string> information);
    };

}

#endif //CERTIFICATEDETAILWIDGET_H
