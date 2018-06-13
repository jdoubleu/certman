#include "CertificateAssistant.h"
#include "ui_certificateassistant.h"
#include "../../core/Environment.h"
#include <string>
#include <QStringList>
#include <QDate>

using std::string;
using core::Environment;

using namespace gui::assistant;

CertificateAssistant::CertificateAssistant(QWidget *parent) : QWizard(parent),
                                                              ui(new Ui::CertificateAssistant) {
    ui->setupUi(this);

    // Fill country name field with iso3166 alpha2 codes
    for (string cc : Environment::iso3166_alpha2_codes_list) {
        ui->countryName_field->addItem(QString::fromStdString(cc));
    }
    ui->countryName_field->setCurrentText(QLocale::system().name().remove(0, 3));

    // validity
    auto now = QDate::currentDate();
    ui->validityperiod_from_field->setText(
            now.toString(QLocale::system().dateFormat(QLocale::LongFormat))
            );

    auto update_validityPeriod_until_field = [=](int v) {
        auto to = now.addDays(v);

        ui->validityperiod_until_field->setText(
                to.toString(QLocale::system().dateFormat(QLocale::LongFormat))
        );
    };
    update_validityPeriod_until_field(ui->validityperiod_field->value());

    connect(ui->validityperiod_field, QOverload<int>::of(&QSpinBox::valueChanged), this, update_validityPeriod_until_field);
}

CertificateAssistant::~CertificateAssistant() {
    delete ui;
}

void CertificateAssistant::accept() {
    QDialog::accept();
}
