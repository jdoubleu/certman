#include "KeyPairWidgetPage.h"
#include "ui_keypairwidgetpage.h"

using namespace gui::assistant::page;

KeyPairWidgetPage::KeyPairWidgetPage(QWidget *parent) : QWizardPage(parent), ui(new Ui::KeyPairWidgetPage) {
    ui->setupUi(this);
}

KeyPairWidgetPage::~KeyPairWidgetPage() {
    delete ui;
}

void KeyPairWidgetPage::injectCertificateManager(CertificateManager *crtMgr) {
    ui->keyPairWidget->injectCertificateManager(crtMgr);
}
