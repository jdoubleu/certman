#ifndef CERTIFICATELISTWIDGET_H
#define CERTIFICATELISTWIDGET_H

#include <QTreeWidget>
#include <unordered_set>
#include "../../cert/Certificate.h"

using std::string;
using std::unordered_set;
using cert::Certificate;

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

        void showCertificates(const unordered_set<Certificate *> &certificates);

    private:
        Ui::CertificateList *ui;
        QTreeWidget *treeList;

        QTreeWidgetItem *createRowForCertificate(Certificate *cert);

    private slots:

        void onItemDoubleClicked(QTreeWidgetItem *item);

    signals:

        void certificateSelected(Certificate *cert);
    };

}

Q_DECLARE_METATYPE(gui::widget::CertificateContainer);

#endif