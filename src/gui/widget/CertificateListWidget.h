#ifndef CERTIFICATELISTWIDGET_H
#define CERTIFICATELISTWIDGET_H

#include <QTreeWidget>
#include <unordered_set>
#include <vector>
#include "src/cert/Certificate.h"
#include "src/cert/CertificateList.h"

using std::string;
using std::unordered_set;
using std::vector;
using cert::Certificate;
using cert::CertificateList;

namespace Ui {
    class CertificateList;
}

namespace gui::widget {

    /**
     * Class represents a widget to show a certificateList.
     */
    class CertificateListWidget : public QWidget {
    Q_OBJECT
    public:

        /**
         * Constructor for a certificateListWidget.
         * @param parent Parent Widget.
         */
        explicit CertificateListWidget(QWidget *parent = 0);

        /**
         * Destructor for a certificateListWidget.
         */
        ~CertificateListWidget();

        /**
         * Clear the list of certificates.
         */
        void clear();

        /**
         * Check if the list is empty.
         * @return Boolean if the list is empty.
         */
        bool isEmpty();

        /**
         * Show all certificates.
         * @param list Set of certificates to show.
         */
        void showCertificates(
                unordered_set<Certificate *, CertificateList::CertificateHashByThumbprint, CertificateList::CertificateEqualByThumbprint> list);

    private:

        /**
         *Ui element of the certificateList.
         */
        Ui::CertificateList *ui;

        /**
         * QTreeWidget element for the list.
         */
        QTreeWidget *treeList;

        /**
         * Creates a row for a certificate inside the list.
         * @param cert Certificate to create row for.
         * @return QTreeWidgetItem containing the new row.
         */
        QTreeWidgetItem *createRowForCertificate(Certificate *cert);

        /**
         * Gets a certificate from a row.
         * @param item Row to get certificate from.
         * @return Certificate of the row.
         */
        Certificate *retrieveCertificateFromItem(const QTreeWidgetItem *item) const;

    private slots:

        /**
         * Eventhandler for a click event on an item.
         * @param item Clicked item.
         */
        void onItemDoubleClicked(QTreeWidgetItem *item);

        /**
         * Eventhandler for a change event on an item.
         */
        void onItemSelectionChanged();

        /**
         * Generates a context menu for a position.
         * @param pos Position to generate context menu for.
         */
        void generateContextMenu(const QPoint &pos);

    signals:

        /**
         * Signal for a certificateSelected.
         * @param cert Selected certificate.
         */
        void certificateSelected(Certificate *cert);

        /**
         * Signal for certificatesSelected.
         * @param certificates Selected certificates.
         */
        void certificatesSelected(vector<Certificate *> certificates);

        /**
         * Signal for certificateRemove.
         */
        void certificateRemoveAction();

        /**
         * Signal for certificateExport.
         */
        void certificateExportAction();

        /**
         * Signal for certificateSign.
         */
        void certificateSignAction();
    };

}

#endif
