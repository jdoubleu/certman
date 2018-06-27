#include "PasswordWidget.h"
#include "ui_passwordwidget.h"

using namespace gui::widget;

PasswordWidget::PasswordWidget(const QString name, QWidget *parent): PasswordWidget(name, NULL, parent) {
}

PasswordWidget::PasswordWidget(const QString name, const QString description, QWidget *parent): QWidget(parent), ui(new Ui::PasswordWidget) {
    ui->setupUi(this);

    this->name = name;
    this->description = description;
}

PasswordWidget::~PasswordWidget() {
    delete ui;
}
