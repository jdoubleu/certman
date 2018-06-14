#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "../../cert/CertificateManager.h"
#include "../../core/Environment.h"
#include "../widget/CertificateListWidget.h"

using cert::CertificateManager;
using core::Environment;
using gui::widget::CertificateListWidget;
using std::vector;

namespace Ui {
    class MainWindow;
}

namespace gui::window {

    class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(CertificateManager *crtMgr, Environment *env, QWidget *parent = 0);

        ~MainWindow();

    private:
        Ui::MainWindow *ui;

        CertificateManager *crtMgr;
        Environment *env;

        CertificateListWidget *crtList;

        Certificate *selectedCertificate;

        void setupActions();

    private slots:

        void importCertificate();

        void onCertificateImport(bool successful);

        void onCertificateDetailsAction();

        void onCertificateExportAction();

        void onCertificateSelected(Certificate *cert);

        void onCertificatesSelected(vector<Certificate *> certificates);

        void onCertificateRemoveAction();
    };

}

#endif
