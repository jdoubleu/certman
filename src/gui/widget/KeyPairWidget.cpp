#include "KeyPairWidget.h"
#include "ui_keypairwidget.h"

using namespace gui::widget;

KeyPairWidget::KeyPairWidget(QWidget *parent): QWidget(parent), ui(new Ui::KeyPairWidget) {
    ui->setupUi(this);
}

KeyPairWidget::~KeyPairWidget() {
    delete ui;
}
