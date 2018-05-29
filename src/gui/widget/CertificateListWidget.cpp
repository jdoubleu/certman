#include "CertificateListWidget.h"
#include "ui_certificatelist.h"
#include "../../cert/Util.h"

using Qt::Orientation;
using cert::time_to_string;

using namespace gui::widget;

CertificateListWidget::CertificateListWidget(QWidget *parent) : QWidget(parent), ui(new Ui::CertificateList) {
    ui->setupUi(this);

    treeList = ui->treeWidget;

    connect(treeList, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(
            onItemDoubleClicked(QTreeWidgetItem *)));
}

CertificateListWidget::~CertificateListWidget() {
    delete ui;
}

void CertificateListWidget::clear() {
    treeList->clear();
}

bool CertificateListWidget::isEmpty() {
    return treeList->topLevelItemCount() == 0;
}

void CertificateListWidget::showCertificates(const unordered_set<Certificate *> &certificates) {
    if (!isEmpty()) {
        clear();
    }

    QList<QTreeWidgetItem *> items;
    unordered_set<Certificate *>::const_iterator it;
    int i = 0;

    for (it = certificates.begin(); it != certificates.end(); ++it, i++) {
        items.append(createRowForCertificate(*it));
    }

    ui->treeWidget->insertTopLevelItems(0, items);

    ui->treeWidget->resizeColumnToContents(0);
    ui->treeWidget->resizeColumnToContents(2);
    ui->treeWidget->resizeColumnToContents(3);
    ui->treeWidget->resizeColumnToContents(4);
}

QTreeWidgetItem* CertificateListWidget::createRowForCertificate(Certificate *cert) {
    auto row = new QTreeWidgetItem(QStringList(
            {
                    QString::fromStdString(cert->getSubjectField("commonName")),
                    QString::fromStdString(cert->getIssuerField("commonName")),
                    QString::fromStdString(time_to_string(cert->getCreated())),
                    QString::fromStdString(time_to_string(cert->getExpires())),
                    QString::fromStdString(cert->getThumbprint())
            }
    ));

    struct CertificateContainer c = {cert};
    row->setData(0, Qt::UserRole, QVariant::fromValue(c));

    return row;
}

void CertificateListWidget::onItemDoubleClicked(QTreeWidgetItem *item) {
    auto c = item->data(0, Qt::UserRole).value<CertificateContainer>().certificate;

    emit certificateSelected(c);
}
