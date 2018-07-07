#include "NameWidget.h"
#include "ui_namewidget.h"
#include "../../core/Environment.h"

using core::Environment;

using namespace gui::widget;

NameWidget::NameWidget(QWidget *parent) : QWidget(parent), ui(new Ui::NameWidget) {
    ui->setupUi(this);

    ui->commonName_field->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9*.]+"), this));
    ui->countryName_field->setValidator(new QRegExpValidator(QRegExp("[A-Z]{2}"), this));

    on_optional_fields_toggle_stateChanged(0);

    // Fill country name field with iso3166 alpha2 codes
    for (const string &cc : Environment::iso3166_alpha2_codes_list) {
        ui->countryName_field->addItem(QString::fromStdString(cc));
    }
    ui->countryName_field->setCurrentText(QLocale::system().name().remove(0, 3));

    connectChildrenChangeEvents();

    renderValidation();
}

NameWidget::~NameWidget() {
    delete ui;
}

void NameWidget::on_optional_fields_toggle_stateChanged(int state) {
    ui->fields_tabs->setTabEnabled(1, state >= 1);
}

X509_NAME *NameWidget::generateX509Name() {
    X509_NAME *name = X509_NAME_new();

    // Fill X509_NAME struct from fields
    certman_qt_X509_NAME_add_entry(NID_commonName, ui->commonName_field);
    certman_qt_X509_NAME_add_entry(NID_organizationName, ui->organization_field);
    certman_qt_X509_NAME_add_entry(NID_organizationalUnitName, ui->organizationalunit_field);
    certman_X509_NAME_add_entry(NID_countryName,
                                (unsigned char *) ui->countryName_field->currentText().toStdString().c_str());
    certman_qt_X509_NAME_add_entry(NID_localityName, ui->locality_field);
    certman_qt_X509_NAME_add_entry(NID_stateOrProvinceName, ui->stateorprovince_field);

    if (!ui->optional_fields_tab->isHidden()) {
        certman_qt_X509_NAME_add_entry(NID_pseudonym, ui->pseudonym_field);
        certman_qt_X509_NAME_add_entry(NID_title, ui->title_field);
        certman_qt_X509_NAME_add_entry(NID_surname, ui->surname_field);
        certman_qt_X509_NAME_add_entry(NID_givenName, ui->givenName_field);
        certman_qt_X509_NAME_add_entry(NID_initials, ui->initials_field);
        certman_qt_X509_NAME_add_entry(NID_generationQualifier, ui->generationQualifier_field);
    }

    return name;
}

X509_NAME *NameWidget::value() {
    X509_NAME *name = NULL;

    if (ui->commonName_field->hasAcceptableInput()) {
        name = generateX509Name();
    }

    return name;
}

void NameWidget::setValue(X509_NAME *name) {
    certman_qt_X509_NAME_get_entry(name, NID_commonName, ui->commonName_field);
    certman_qt_X509_NAME_get_entry(name, NID_organizationName, ui->organization_field);
    certman_qt_X509_NAME_get_entry(name, NID_organizationalUnitName, ui->organizationalunit_field);
    certman_qt_X509_NAME_get_entry(name, NID_localityName, ui->locality_field);
    certman_qt_X509_NAME_get_entry(name, NID_stateOrProvinceName, ui->stateorprovince_field);

    char *countryNameBuf;
    certman_X509_NAME_get_entry(name, NID_countryName, countryNameBuf);
    bool countryNameSignalsBlocked = ui->countryName_field->blockSignals(true);
    ui->countryName_field->setCurrentText(QString(countryNameBuf));
    ui->countryName_field->blockSignals(countryNameSignalsBlocked);

    certman_qt_X509_NAME_get_entry(name, NID_pseudonym, ui->pseudonym_field);
    certman_qt_X509_NAME_get_entry(name, NID_title, ui->title_field);
    certman_qt_X509_NAME_get_entry(name, NID_surname, ui->surname_field);
    certman_qt_X509_NAME_get_entry(name, NID_givenName, ui->givenName_field);
    certman_qt_X509_NAME_get_entry(name, NID_initials, ui->initials_field);
    certman_qt_X509_NAME_get_entry(name, NID_generationQualifier, ui->generationQualifier_field);

    if (ui->pseudonym_field->hasAcceptableInput() || ui->title_field->hasAcceptableInput() ||
        ui->surname_field->hasAcceptableInput() || ui->givenName_field->hasAcceptableInput() ||
        ui->initials_field->hasAcceptableInput() || ui->generationQualifier_field->hasAcceptableInput()) {
        ui->optional_fields_toggle->setChecked(true);
    }

    fieldValueChanged();
}

void NameWidget::reset() {
    QList<QLineEdit *> editFields = findChildren<QLineEdit *>();
    for (QLineEdit *field: editFields) {
        field->clear();
    }

    ui->countryName_field->setCurrentText(QLocale::system().name().remove(0, 3));

    ui->optional_fields_toggle->setChecked(false);
}

void NameWidget::connectChildrenChangeEvents() {
    QList<QLineEdit *> editFields = findChildren<QLineEdit *>();
    for (QLineEdit *field: editFields) {
        connect(field, &QLineEdit::textChanged, this, &NameWidget::fieldValueChanged);
    }

    connect(ui->countryName_field, &QComboBox::currentTextChanged, this, &NameWidget::fieldValueChanged);
}

void NameWidget::fieldValueChanged() {
    renderValidation();

    emit valueChanged();
}

void NameWidget::renderValidation() {
    if (!ui->commonName_field->hasAcceptableInput()) {
        ui->errorMessage->setText(tr("Common Name must be filled!"));
    } else {
        ui->errorMessage->setText(NULL);
    }
}
