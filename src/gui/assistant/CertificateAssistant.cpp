#include "CertificateAssistant.h"
#include "ui_certificateassistant.h"
#include <QPushButton>

using namespace gui::assistant;

CertificateAssistant::CertificateAssistant(QWidget *parent) : QDialog(parent),
                                                              ui(new Ui::CertificateAssistant) {
    ui->setupUi(this);

    setupDialogButtons();
}

CertificateAssistant::~CertificateAssistant() {
    delete ui;
}

void CertificateAssistant::setupDialogButtons() {
    auto nextButton = new QPushButton(tr("Continue"));
    nextButton->setDefault(true);

    auto previousButton = new QPushButton(tr("Back"));

    ui->dialog_buttons->addButton(nextButton, QDialogButtonBox::ApplyRole);
    ui->dialog_buttons->addButton(previousButton, QDialogButtonBox::ResetRole);

    connect(nextButton, &QAbstractButton::clicked, this, [=] {
        int current = ui->pages_widget->currentIndex();

        ui->pages_widget->setCurrentIndex(current + 1);
    });

    connect(previousButton, &QAbstractButton::clicked, this, [=] {
        int current = ui->pages_widget->currentIndex();

        ui->pages_widget->setCurrentIndex(current - 1);
    });
}
