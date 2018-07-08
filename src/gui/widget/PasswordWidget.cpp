#include "PasswordWidget.h"
#include "ui_passwordwidget.h"
#include "ui_passworddialog.h"
#include <QPushButton>

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

    return validate() ? ui->passwordLineEdit->text().toStdString() : "";
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

    emit passwordChanged();
}

void PasswordWidget::on_repeatPasswordLineEdit_textChanged(const QString &value) {
    validate();

    emit passwordChanged();
}

QDialog *PasswordWidget::asDialog(const QString name, const QString description, bool repeat, QWidget *parent) {
    auto *dialogUi = new Ui::PasswordDialog;
    auto *dialog = new QDialog(parent);
    dialogUi->setupUi(dialog);

    dialog->setWindowTitle(name);

    PasswordWidget *passwordWidget = dialogUi->passwordWidget;
    passwordWidget->setName(name);
    passwordWidget->setDescription(description);
    passwordWidget->setRepeat(repeat);

    auto *okButton = dialogUi->buttonBox->button(QDialogButtonBox::Ok);
    okButton->setAutoDefault(false);
    okButton->setCheckable(false);
    
    connect(passwordWidget, &PasswordWidget::passwordChanged, [&okButton, &passwordWidget]() {
        okButton->setCheckable(passwordWidget->validate());
    });

    return dialog;
}

string PasswordWidget::passwordDialog(const QString name, const QString description, bool repeat, QWidget *parent) {
    auto *dialog = PasswordWidget::asDialog(name, description, repeat, parent);

    if (dialog->exec() == QDialog::Accepted) {
        auto *widget = dialog->findChild<PasswordWidget *>("passwordWidget");

        if (!widget) {
            // TODO: throw exception
            return "";
        }

        return widget->password();
    }

    return "";
}
