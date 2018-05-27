#include <QTreeWidget>
#include <unordered_set>
#include "src/cert/Certificate.h"
#include "src/cert/CertificateList.h"

using std::string;
using std::unordered_set;
using cert::Certificate;
using cert::CertificateList;

namespace Ui {
    class CertificateList;
}

namespace gui::widget {

    class CertificateListWidget : public QWidget {
    public:
        explicit CertificateListWidget(QWidget *parent = 0);

        ~CertificateListWidget();

        void clear();

        bool isEmpty();

        void showCertificates(
                unordered_set<Certificate *, CertificateList::CertificateHashByThumbprint, CertificateList::CertificateEqualByThumbprint>);

    private:
        Ui::CertificateList *ui;

        QAbstractItemModel *model;

        void certToRow(Certificate *cert, const int &row);

        QVariant cellFactory(const string &content);
    };

}
