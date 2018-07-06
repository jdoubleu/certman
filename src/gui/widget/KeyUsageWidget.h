#ifndef KEYUSAGEWIDGET_H
#define KEYUSAGEWIDGET_H

#include <QWidget>
#include <openssl/x509v3.h>

namespace Ui {
    class KeyUsageWidget;
}

namespace gui::widget {
    class KeyUsageWidget : public QWidget {
    Q_OBJECT

    public:
        explicit KeyUsageWidget(QWidget *parent);

        ~KeyUsageWidget();

        bool isEnabled();

        X509_EXTENSION *getKeyUsageExtensions();

    private:
        Ui::KeyUsageWidget *ui;

    };
}


#endif
