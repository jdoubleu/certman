#include "NameWidgetPage.h"
#include "ui_namewidgetpage.h"

using namespace gui::assistant::page;

NameWidgetPage::NameWidgetPage(QWidget *parent) : QWizardPage(parent), ui(new Ui::NameWidgetPage) {
    ui->setupUi(this);

    registerField("nameWidget*", ui->nameWidget, "value", SIGNAL(valueChanged()));
}

NameWidgetPage::~NameWidgetPage() {
    delete ui;
}
