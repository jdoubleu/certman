#ifndef CERTIFICATEDETAILWIDGET_H
#define CERTIFICATEDETAILWIDGET_H

#include <QWidget>
#include <QFormLayout>
#include <QGroupBox>
#include <QDialog>
#include <QTreeWidgetItem>
#include "../../cert/Certificate.h"
#include "../../cert/CertificateManager.h"

using cert::Certificate;
using cert::CertificateManager;

namespace Ui {
    class CertificateDetail;
}

namespace gui::widget {

    /**
     * Class represents a widget for a certificate detail view.
     */
    class CertificateDetailWidget : public QWidget {
    Q_OBJECT
    public:

        /**
         * Constructor for a certificateDetailWidget.
         * @param certificate Certificate to show details of.
         * @param crtMgr CertificateManager to get all information of the certificate.
         * @param parent Parent of the widget.
         */
        explicit CertificateDetailWidget(Certificate certificate, CertificateManager *crtMgr,
                                         QWidget *parent);

        /**
         * Destructor of a certificateDetailWidget.
         */
        ~CertificateDetailWidget();

        /**
         * Displays the widget as a dialog.
         * @param certificate Certificate to show details of.
         * @param crtMgr CertificateManager to get all information of the certificate.
         * @param parent Parent of the widget.
         * @return QDialog containing the certificate detail view.
         */
        static QDialog *asDialog(Certificate certificate, CertificateManager *crtMgr, QWidget *parent = 0);

    private:
        /**
         * Ui for the certificateDetailWidget.
         */
        Ui::CertificateDetail *ui;

        /**
         * Certificate to show details from.
         */
        Certificate cert;

        /**
         * CertificateManager to get all details of the certificate.
         */
        CertificateManager *crtMgr;

        /**
         * Renders the view of the certificate.
         */
        void renderCertificate();

        /**
         * Renders the certificatePath.
         */
        void renderCertificatePath();

        /**
         * Creates a widget for a detail section.
         * @param name Name of the detail section.
         * @return Created QWidget.
         */
        QWidget *createDetailSection(QString name);

        /**
         * Creates an informationTable.
         * @param attachTo QWidget to attach the informationTable to.
         * @param information Map of information to display.
         */
        void createInformationTable(QWidget *attachTo, map<string, string> information);

        /**
         * Creates a detailInformationSection.
         * @param name Name of the detailInformationSection.
         * @param information Information to display.
         */
        void createDetailInformationSection(QString name, map<string, string> information);

        /**
         * Creates a function to call on a click event inside the certificatePath.
         * @param item Clicked item.
         * @param column IGNORED
         */
        void onCertificatePathItemDoubleClicked(QTreeWidgetItem *item, int column);

        /**
         * Renders all extensions.
         */
        void renderExtensions();
    };

}

#endif //CERTIFICATEDETAILWIDGET_H
