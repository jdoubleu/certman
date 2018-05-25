#include <QTreeWidget>
#include "../../cert/Certificate.h"

using std::string;
using std::vector;
using cert::Certificate;

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

        void showCertificates(const vector<Certificate *> &certificates);

    private:
        Ui::CertificateList *ui;
        QAbstractItemModel *model;

        void certToRow(Certificate *cert, const int &row);

        QVariant cellFactory(const string &content);
    };

}
