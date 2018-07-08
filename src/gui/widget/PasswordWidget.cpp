#include "PasswordWidget.h"
#include "ui_passwordwidget.h"

using namespace gui::widget;

PasswordWidget::PasswordWidget(QWidget *parent) : PasswordWidget(NULL, NULL, false, parent) {
}

PasswordWidget::PasswordWidget(const QString name, QWidget *parent) : PasswordWidget(name, NULL, false, parent) {
}

PasswordWidget::PasswordWidget(QString name, bool repeat, QWidget *parent) : PasswordWidget(name, NULL, repeat,
                                                                                            parent) {
}

PasswordWidget::PasswordWidget(const QString name, const QString description, bool repeat, QWidget *parent) : QWidget(
        parent), ui(new Ui::PasswordWidget) {
    ui->setupUi(this);

    setName(name);
    setDescription(description);
    setRepeat(repeat);
}

PasswordWidget::~PasswordWidget() {
    delete ui;
}

bool PasswordWidget::validate() {
    if (ui->passwordLineEdit->text().isEmpty()) {
        ui->validationMessage->setText(tr("Password must not be empty!"));

        return false;
    } else if (this->repeat &&
               ui->passwordLineEdit->text().compare(ui->repeatPasswordLineEdit->text(), Qt::CaseSensitive)) {
        ui->validationMessage->setText(tr("Passwords do not match!"));

        return false;
    } else {
        ui->validationMessage->clear();

        return true;
    }
}

string PasswordWidget::password() {
    // TODO: use BIO_s_secmem
    // TODO: use utf8 compatible format
    return ui->passwordLineEdit->text().toStdString();
}

BIO *PasswordWidget::securePassphrase() {
    BIO *passphrase = BIO_new(BIO_s_secmem());
    BIO_puts(passphrase, password().c_str());
    // TODO: make bio read-only

    return passphrase;
}

void PasswordWidget::setName(QString name) {
    this->name = name;

    ui->passwordLabel->setText(name != NULL ? name : "");
}

void PasswordWidget::setDescription(QString description) {
    this->description = description;

    ui->descriptionLabel->setText(description != NULL ? description : "");
    ui->descriptionLabel->setHidden(description == NULL);
}

void PasswordWidget::setRepeat(bool repeat) {
    this->repeat = repeat;

    ui->repeatPasswordLabel->setHidden(!repeat);
    ui->repeatPasswordLineEdit->setHidden(!repeat);
}

void PasswordWidget::on_passwordLineEdit_textChanged(const QString &value) {
    validate();
}

void PasswordWidget::on_repeatPasswordLineEdit_textChanged(const QString &value) {
    validate();
}
