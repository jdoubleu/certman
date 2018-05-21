#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "../assistant/ImportAssistant.h"

using gui::assistant::ImportAssistant;

using namespace gui::window;

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);

    this->setupActions();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setupActions() {
    connect(ui->action_Import, SIGNAL(triggered()), this, SLOT(importCertificate()));
}

void MainWindow::importCertificate() {
    ImportAssistant ia;
    ia.exec();
}
