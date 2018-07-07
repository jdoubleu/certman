#ifndef NAMEWIDGET_H
#define NAMEWIDGET_H

#include <QWidget>
#include <openssl/x509.h>

#define certman_X509_NAME_add_entry(n, v) X509_NAME_add_entry_by_NID(name, n, V_ASN1_UTF8STRING, v, -1, -1, 0);
#define certman_qt_X509_NAME_add_entry(n, v) { QString text = (v)->text(); \
    if (!text.isEmpty()) X509_NAME_add_entry_by_NID(name, n, V_ASN1_UTF8STRING, (unsigned char *) text.toStdString().c_str(), -1, -1, 0); }

#define certman_X509_NAME_get_entry(name, nid, bref) {\
        int length = X509_NAME_get_text_by_NID(name, nid, NULL, 0); \
        X509_NAME_get_text_by_NID(name, nid, bref, length + 1); \
    }

#define certman_qt_X509_NAME_get_entry(name, nid, f) {\
        char *cbuf = NULL; \
        certman_X509_NAME_get_entry(name, nid, cbuf); \
        bool signalsBlocked = (f)->blockSignals(true); \
        (f)->setText(QString(cbuf)); \
        (f)->blockSignals(signalsBlocked); \
    }

namespace Ui {
    class NameWidget;
}

namespace gui::widget {

    class NameWidget : public QWidget {
    Q_OBJECT
        Q_PROPERTY(X509_NAME *value
                           READ value
                           WRITE setValue
                           RESET reset
                           NOTIFY valueChanged
                           DESIGNABLE
                           false
                           SCRIPTABLE
                           false
                           STORED
                           false)

    public:
        explicit NameWidget(QWidget *parent);

        ~NameWidget();

        X509_NAME *generateX509Name();

        X509_NAME *value();

        void setValue(X509_NAME *name);

        void reset();

    public Q_SLOTS:

        void on_optional_fields_toggle_stateChanged(int state);

        void fieldValueChanged();

    private:

        Ui::NameWidget *ui;

        void connectChildrenChangeEvents();

        void renderValidation();

    Q_SIGNALS:

        void valueChanged();

    };

}

Q_DECLARE_OPAQUE_POINTER(X509_NAME*);

Q_DECLARE_METATYPE(X509_NAME*);

#endif //NAMEWIDGET_H
