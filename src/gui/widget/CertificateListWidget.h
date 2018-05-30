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

    struct CertificateContainer {
        Certificate *certificate;
    };

    class CertificateListWidget : public QWidget {
    Q_OBJECT
    public:
        explicit CertificateListWidget(QWidget *parent = 0);

        ~CertificateListWidget();

        void clear();

        bool isEmpty();

        void showCertificates(
                unordered_set<Certificate *, CertificateList::CertificateHashByThumbprint, CertificateList::CertificateEqualByThumbprint>);

    private:
        Ui::CertificateList *ui;
        QTreeWidget *treeList;

        QTreeWidgetItem *createRowForCertificate(Certificate *cert);

        Certificate *retrieveCertificateFromItem(const QTreeWidgetItem *item) const;

    private slots:

        void onItemDoubleClicked(QTreeWidgetItem *item);

        void onItemSelectionChanged();

        void generateContextMenu(const QPoint &pos);

    signals:

        void certificateSelected(Certificate *cert);

        void certificatesSelected(vector<Certificate *> certificates);
    };

}

Q_DECLARE_METATYPE(gui::widget::CertificateContainer);

#endif
