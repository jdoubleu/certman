#include "CAAssistant.h"
#include "ui_caassistant.h"

using namespace gui::assistant;

CAAssistant::CAAssistant(CertificateManager *crtMgr, QWidget *parent): QWizard(parent), ui(new Ui::CAAssistant), crtMgr(crtMgr) {
    ui->setupUi(this);
}

CAAssistant::~CAAssistant() {
    delete ui;
}
