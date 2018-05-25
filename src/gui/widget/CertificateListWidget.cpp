#include "CertificateListWidget.h"
#include "ui_certificatelist.h"
#include <QTableWidgetItem>
#include <QTreeWidgetItem>
#include <time.h>

using Qt::Orientation;

using namespace gui::widget;

CertificateListWidget::CertificateListWidget(QWidget *parent) : QWidget(parent), ui(new Ui::CertificateList) {
    ui->setupUi(this);

    model = ui->treeWidget->model();
}

CertificateListWidget::~CertificateListWidget() {
    delete ui;
}

void CertificateListWidget::clear() {
    model->removeRows(0, ui->treeWidget->model()->rowCount());
}

bool CertificateListWidget::isEmpty() {
    return model->rowCount() == 0;
}

void CertificateListWidget::showCertificates(const vector<Certificate *> &certificates) {
    if (!isEmpty()) {
        clear();
    }

    model->insertRows(0, certificates.size());

    vector<Certificate *>::const_iterator it;
    int i = 0;

    for (it = certificates.begin(); it != certificates.end(); ++it, i++) {
        Certificate *cert = *it;
        certToRow(cert, i);
    }

    ui->treeWidget->resizeColumnToContents(0);
    ui->treeWidget->resizeColumnToContents(2);
    ui->treeWidget->resizeColumnToContents(3);
    ui->treeWidget->resizeColumnToContents(4);
}

void CertificateListWidget::certToRow(Certificate *cert, const int &row) {
    auto subject = cert->getSubjectNAME();

    auto asn_str = X509_NAME_ENTRY_get_data(X509_NAME_get_entry(subject, 5));
    string common_name = string((char *) ASN1_STRING_get0_data(asn_str));

    model->setData(model->index(row, 0), cellFactory(common_name));

    asn_str = X509_NAME_ENTRY_get_data(X509_NAME_get_entry(cert->getIssuerNAME(), 5));
    common_name = string((char *) ASN1_STRING_get0_data(asn_str));

    model->setData(model->index(row, 1), cellFactory(common_name));

    time_t _tm = cert->getCreated();
    struct tm * curtime = gmtime(&_tm);

    model->setData(model->index(row, 2), cellFactory(asctime(curtime)));
    model->setData(model->index(row, 3), cellFactory(asctime(curtime)));
    model->setData(model->index(row, 4), cellFactory(cert->getThumbprint()));
}

QVariant CertificateListWidget::cellFactory(const string &content) {
    return QString::fromStdString(content);
}
