#ifndef NAMEWIDGET_H
#define NAMEWIDGET_H

#include <QWidget>
#include <openssl/x509.h>

#define certman_X509_NAME_add_entry(n, v) X509_NAME_add_entry_by_NID(name, n, MBSTRING_UTF8, v, -1, -1, 0);
#define certman_qt_X509_NAME_add_entry(n, v) { QString text = (v)->text(); \
    if (!text.isEmpty()) X509_NAME_add_entry_by_NID(name, n, MBSTRING_UTF8, (unsigned char *) text.toStdString().c_str(), -1, -1, 0); }

namespace Ui {
    class NameWidget;
}

namespace gui::widget {

    class NameWidget : public QWidget {
    Q_OBJECT

    public:
        explicit NameWidget(QWidget *parent);

        ~NameWidget();

        bool validate();

        X509_NAME *getX509Name();

    public Q_SLOTS:

        void on_optional_fields_toggle_stateChanged(int state);

    private:

        Ui::NameWidget *ui;
    };

}


#endif //NAMEWIDGET_H
