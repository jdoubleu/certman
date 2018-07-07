#ifndef KEYUSAGEWIDGET_H
#define KEYUSAGEWIDGET_H

#include <QWidget>
#include <openssl/x509v3.h>
#include "../../cert/CertificateManager.h"

using cert::CertificateManager;

namespace Ui {
    class KeyUsageWidget;
}

namespace gui::widget {
    class KeyUsageWidget : public QWidget {
    Q_OBJECT

    public:
        explicit KeyUsageWidget(CertificateManager *crtMgr, QWidget *parent);

        explicit KeyUsageWidget(QWidget *parent);

        ~KeyUsageWidget();

        bool isEnabled();

        X509_EXTENSION *getKeyUsageExtensions();

        void injectCertificateManager(CertificateManager *crtMgr);

    private:
        Ui::KeyUsageWidget *ui;

        CertificateManager *crtMgr;

    };
}


#endif
