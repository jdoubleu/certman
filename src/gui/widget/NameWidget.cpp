#include "NameWidget.h"
#include "ui_namewidget.h"
#include "../../core/Environment.h"

using core::Environment;

using namespace gui::widget;

NameWidget::NameWidget(QWidget *parent): QWidget(parent), ui(new Ui::NameWidget) {
    ui->setupUi(this);

    on_optional_fields_toggle_stateChanged(0);

    // Fill country name field with iso3166 alpha2 codes
    for (const string &cc : Environment::iso3166_alpha2_codes_list) {
        ui->countryName_field->addItem(QString::fromStdString(cc));
    }
    ui->countryName_field->setCurrentText(QLocale::system().name().remove(0, 3));
}

NameWidget::~NameWidget() {
    delete ui;
}

void NameWidget::on_optional_fields_toggle_stateChanged(int state) {
    ui->fields_tabs->setTabEnabled(1, state >= 1);
}

X509_NAME *NameWidget::getX509Name() {
    X509_NAME *name = X509_NAME_new();

    // Fill X509_NAME struct from fields
    certman_qt_X509_NAME_add_entry(NID_commonName, ui->commonName_field);
    certman_qt_X509_NAME_add_entry(NID_organizationName, ui->organization_field);
    certman_qt_X509_NAME_add_entry(NID_organizationalUnitName, ui->organizationalunit_field);
    certman_X509_NAME_add_entry(NID_countryName, (unsigned char *) ui->countryName_field->currentText().toStdString().c_str());
    certman_qt_X509_NAME_add_entry(NID_localityName, ui->locality_field);
    certman_qt_X509_NAME_add_entry(NID_stateOrProvinceName, ui->stateorprovince_field);
    certman_qt_X509_NAME_add_entry(NID_organizationName, ui->organization_field);

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

bool NameWidget::validate() {
    return true;
}


