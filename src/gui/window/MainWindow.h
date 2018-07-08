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

    /**
     * Represents the main interaction point with the application.
     */
    class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        /**
         * Constructor for the Window.
         * @param crtMgr Instance of certificate manager.
         * @param parent Parent widget.
         */
        explicit MainWindow(CertificateManager *crtMgr, QWidget *parent = 0);

        /**
         * Destructor for the Window.
         */
        ~MainWindow();

    private:
        /**
         * Instance of the window ui.
         */
        Ui::MainWindow *ui;

        /**
         * Instance of the certificate manager.
         */
        CertificateManager *crtMgr;

        /**
         * Instance of the certificate list widget.
         */
        CertificateListWidget *crtList;

        /**
         * Reference to the selected certificate.
         */
        Certificate *selectedCertificate;

        /**
         * Setup the the window state.
         */
        void setupActions();

    private slots:

        /**
         * Selects the certificate.
         * @param certificates Selected certificates.
         */
        void onCertificatesSelected(vector<Certificate *> certificates);

        /**
         * Opens the import assistant.
         */
        void importCertificate();

        /**
         * Handle the result of the import.
         * @param successful Assistant dialog passed.
         */
        void onCertificateImport(bool successful);

        /**
         * Opens the detail dialog.
         * @param cert Certificate to be viewed.
         */
        void onCertificateSelected(Certificate *cert);

        /**
         * Handle the certificate detail action.
         */
        void onCertificateDetailsAction();

        /**
         * Opens the export assistant dialog.
         */
        void onCertificateExportAction();

        /**
         * Opens the remove certificate dialog.
         */
        void onCertificateRemoveAction();

        /**
         * Opens the new certificate assistant dialog.
         */
        void onNewCertificateAction();

        /**
         * Opens the new certificate authority assistant dialog.
         */
        void onNewCertificateAuthorityAction();

        /**
         * Opens the certificate signing assistant dialog.
         */
        void onCertificateSignAction();
    };

}

#endif
