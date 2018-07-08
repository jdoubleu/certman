#include "KeyPairWidgetPage.h"
#include "ui_keypairwidgetpage.h"

using namespace gui::assistant::page;

KeyPairWidgetPage::KeyPairWidgetPage(QWidget *parent) : QWizardPage(parent), ui(new Ui::KeyPairWidgetPage) {
    ui->setupUi(this);

    registerField("keyPairWidget*", ui->keyPairWidget, "keyPair", SIGNAL(keyPairChanged()));
}

KeyPairWidgetPage::~KeyPairWidgetPage() {
    delete ui;
}

void KeyPairWidgetPage::injectCertificateManager(CertificateManager *crtMgr) {
    ui->keyPairWidget->injectCertificateManager(crtMgr);
}

bool KeyPairWidgetPage::isComplete() const {
    return ui->keyPairWidget->validate();
}

void KeyPairWidgetPage::on_keyPairWidget_keyPairChanged() {
    emit completeChanged();
}
