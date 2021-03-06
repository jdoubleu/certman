#include "CertificateListWidget.h"
#include "ui_certificatelist.h"
#include "../../cert/util.h"
#include <QMenu>

using Qt::Orientation;
using cert::time_to_string;

using namespace gui::widget;

CertificateListWidget::CertificateListWidget(QWidget *parent) : QWidget(parent), ui(new Ui::CertificateList) {
    ui->setupUi(this);

    treeList = ui->treeWidget;

    connect(treeList, SIGNAL(customContextMenuRequested(
                                     const QPoint &)), this, SLOT(generateContextMenu(
                                                                          const QPoint &)));

    connect(treeList, SIGNAL(itemDoubleClicked(QTreeWidgetItem * , int)), this, SLOT(
                                                                                        onItemDoubleClicked(
                                                                                                QTreeWidgetItem * )));
    connect(ui->treeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(onItemSelectionChanged()));
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

void CertificateListWidget::showCertificates(CertificateListSet certificates) {
    if (!isEmpty()) {
        clear();
    }

    QList<QTreeWidgetItem *> items;
    CertificateListSet::const_iterator it;
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

QTreeWidgetItem *CertificateListWidget::createRowForCertificate(Certificate *cert) {
    auto row = new QTreeWidgetItem(QStringList(
            {
                    QString::fromStdString(cert->getSubjectField("commonName")),
                    QString::fromStdString(cert->getIssuerField("commonName")),
                    QString::fromStdString(time_to_string(cert->getCreated())),
                    QString::fromStdString(time_to_string(cert->getExpires())),
                    QString::fromStdString(cert->getThumbprint())
            }
    ));

    row->setData(0, Qt::UserRole, QVariant::fromValue(cert));

    return row;
}

Certificate *CertificateListWidget::retrieveCertificateFromItem(const QTreeWidgetItem *item) const {
    return item->data(0, Qt::UserRole).value<Certificate *>();
}

void CertificateListWidget::onItemDoubleClicked(QTreeWidgetItem *item) {
    auto c = retrieveCertificateFromItem(item);

    emit certificateSelected(c);
}

void CertificateListWidget::onItemSelectionChanged() {
    auto items = ui->treeWidget->selectedItems();

    vector<Certificate *> selectedCertificates;
    QList<QTreeWidgetItem *>::iterator it;

    for (it = items.begin(); it != items.end(); ++it) {
        selectedCertificates.push_back(retrieveCertificateFromItem(*it));
    }

    emit certificatesSelected(selectedCertificates);
}

void CertificateListWidget::generateContextMenu(const QPoint &pos) {
    auto item = treeList->itemAt(pos);

    if (item == NULL) {
        return;
    }

    auto *c = retrieveCertificateFromItem(item);

    QMenu contextMenu(tr("Certificate"), this);

    // Name
    QAction name(QString::fromStdString(c->getSubjectField("commonName")), this);
    name.setDisabled(true);
    contextMenu.addAction(&name);
    QAction nameSep(this);
    nameSep.setSeparator(true);
    contextMenu.addAction(&nameSep);

    // TODO: use same translation ref as from MainWindow certificateMenu actions
    QAction showDetails(tr("Information"), this);
    connect(&showDetails, &QAction::triggered, this, [=] {
        emit certificateSelected(c);
    });
    contextMenu.addAction(&showDetails);

    QAction showRemove(tr("Remove"), this);
    connect(&showRemove, &QAction::triggered, this, [=] {
        emit certificateRemoveAction();
    });
    contextMenu.addAction(&showRemove);

    QAction showExport(tr("Export"), this);
    connect(&showExport, &QAction::triggered, this, [=] {
        emit certificateExportAction();
    });
    contextMenu.addAction(&showExport);

    QAction showSign(tr("Sign"), this);
    connect(&showSign, &QAction::triggered, this, [=] {
        emit certificateSignAction();
    });
    contextMenu.addAction(&showSign);

    contextMenu.exec(mapToGlobal(pos));
}
