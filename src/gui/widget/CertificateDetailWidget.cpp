#include <QLabel>
#include "CertificateDetailWidget.h"
#include "ui_certificatedetail.h"
#include <openssl/safestack.h>

using cert::CertificateContainer;

using namespace gui::widget;

CertificateDetailWidget::CertificateDetailWidget(Certificate certificate, CertificateManager *crtMgr, QWidget *parent) :
        ui(new Ui::CertificateDetail),
        cert(certificate),
        crtMgr(crtMgr) {
    ui->setupUi(this);

    renderCertificate();

    connect(ui->certificate_chain_tree, &QTreeWidget::itemActivated, this, &CertificateDetailWidget::onCertificatePathItemDoubleClicked);
}

CertificateDetailWidget::~CertificateDetailWidget() {
    delete ui;
}

QDialog *CertificateDetailWidget::asDialog(Certificate certificate, CertificateManager *crtMgr, QWidget *parent) {
    auto *dialog = new QDialog(parent);
    dialog->setWindowTitle(QString::fromStdString(certificate.getSubjectField("commonName")));

    auto *layout = new QGridLayout(dialog);
    layout->setMargin(10);

    layout->addWidget(new CertificateDetailWidget(certificate, crtMgr, dialog));

    dialog->setLayout(layout);

    return dialog;
}

void CertificateDetailWidget::renderCertificate() {
    createDetailInformationSection("Subject", cert.getSubjectFields());
    createDetailInformationSection("Issuer", cert.getIssuerFields());

    renderCertificatePath();
}

QWidget *CertificateDetailWidget::createDetailSection(QString name) {
    auto *section = new QGroupBox(ui->certificate_details);
    section->setTitle(name);
    section->setFlat(true);

    ui->certificate_details->layout()->addWidget(section);

    return section;
}

void CertificateDetailWidget::createInformationTable(QWidget *attachTo, map<string, string> information) {
    auto table = new QFormLayout(attachTo);
    table->setMargin(0);
    table->setFormAlignment(Qt::AlignJustify | Qt::AlignTop);

    map<string, string>::iterator it;

    for (it = information.begin(); it != information.end(); it++) {
        table->addRow(
                new QLabel(QString::fromStdString(it->first), attachTo),
                new QLabel(QString::fromStdString(it->second), attachTo)
        );
    }
}

void CertificateDetailWidget::createDetailInformationSection(QString name, map<string, string> information) {
    auto *container = createDetailSection(name);
    createInformationTable(container, information);
}

void CertificateDetailWidget::renderCertificatePath() {
    X509_STORE *store = crtMgr->getCertificateListAsX509Store();

    X509_STORE_CTX *ctx = X509_STORE_CTX_new();
    X509_STORE_CTX_init(ctx, store, cert.getX509(), NULL);

    X509_verify_cert(ctx); // ignore result, but require for chain
    stack_st_X509 *chain = X509_STORE_CTX_get1_chain(ctx);

    QTreeWidgetItem *previous = NULL;

    while (sk_X509_num(chain) > 0) {
        X509 *cert = sk_X509_pop(chain);
        auto *c = new Certificate(cert);

        QStringList text;
        text << QString::fromStdString(c->getSubjectField(SN_commonName));

        auto *cur = new QTreeWidgetItem(text);
        struct CertificateContainer con = {c};
        cur->setData(0, Qt::UserRole, QVariant::fromValue(con));

        if (previous == NULL) {
            ui->certificate_chain_tree->addTopLevelItem(cur);
        } else {
            previous->addChild(cur);
            previous->setExpanded(true);
        }

        previous = cur;
    }

    if (previous != NULL) {
        previous->setFlags(Qt::ItemIsEnabled);
    }
}

void CertificateDetailWidget::onCertificatePathItemDoubleClicked(QTreeWidgetItem *item, int column) {
    if (item == NULL) {
        return;
    }

    auto cert = item->data(0, Qt::UserRole).value<CertificateContainer>().certificate;

    if (*cert == this->cert) {
        return;
    }

    auto dialog = CertificateDetailWidget::asDialog(*cert, crtMgr, this);
    dialog->show();
}
