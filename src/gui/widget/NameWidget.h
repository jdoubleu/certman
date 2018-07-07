#ifndef NAMEWIDGET_H
#define NAMEWIDGET_H

#include <QWidget>
#include <openssl/x509.h>

#define certman_X509_NAME_add_entry(n, v) X509_NAME_add_entry_by_NID(name, n, MBSTRING_UTF8, v, -1, -1, 0);
#define certman_qt_X509_NAME_add_entry(n, v) { QString text = (v)->text(); \
    if (!text.isEmpty()) X509_NAME_add_entry_by_NID(name, n, MBSTRING_UTF8, (unsigned char *) text.toStdString().c_str(), -1, -1, 0); }

#define certman_X509_NAME_get_entry(name, nid, cbuf) \
    int length##nid = X509_NAME_get_text_by_NID(name, nid, NULL, 0); \
    char cbuf##nid[length##nid + 1]; \
    X509_NAME_get_text_by_NID(name, nid, cbuf##nid, length##nid + 1); \
    (cbuf) = cbuf##nid

#define certman_qt_X509_NAME_get_entry(name, nid, f) \
    char *cbuf##nid; \
    certman_X509_NAME_get_entry(name, nid, cbuf##nid); \
    (f)->setText(QString(cbuf##nid));

#define clearLineEdit(f) ui->f->clear();

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

    Q_SIGNALS:

        void valueChanged(X509_NAME *name);

    };

}


#endif //NAMEWIDGET_H
