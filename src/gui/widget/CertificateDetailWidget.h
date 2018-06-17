#ifndef CERTIFICATEDETAILWIDGET_H
#define CERTIFICATEDETAILWIDGET_H

#include <QWidget>
#include <QFormLayout>
#include <QGroupBox>
#include <QDialog>
#include "../../cert/Certificate.h"
#include "../../cert/CertificateManager.h"

using cert::Certificate;
using cert::CertificateManager;

namespace Ui {
    class CertificateDetail;
}

namespace gui::widget {

    class CertificateDetailWidget : public QWidget {
    Q_OBJECT
    public:
        explicit CertificateDetailWidget(Certificate certificate, CertificateManager *crtMgr,
                                                 QWidget *parent);

        ~CertificateDetailWidget();

        static QDialog *asDialog(Certificate certificate, CertificateManager *crtMgr, QWidget *parent = 0);

    private:
        Ui::CertificateDetail *ui;
        Certificate cert;
        CertificateManager *crtMgr;

        void renderCertificate();

        QWidget *createDetailSection(QString name);

        void createInformationTable(QWidget *attachTo, map<string, string> information);

        void createDetailInformationSection(QString name, map<string, string> information);
    };

}

#endif //CERTIFICATEDETAILWIDGET_H
