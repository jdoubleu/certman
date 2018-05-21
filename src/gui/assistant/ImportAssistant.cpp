#include "ImportAssistant.h"
#include "ui_importassistant.h"

using namespace gui::assistant;

ImportAssistant::ImportAssistant(QWidget *parent): QDialog(parent), ui(new Ui::ImportAssistant) {
    ui->setupUi(this);
}

ImportAssistant::~ImportAssistant() {
    delete ui;
}