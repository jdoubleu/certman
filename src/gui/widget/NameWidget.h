#ifndef NAMEWIDGET_H
#define NAMEWIDGET_H

#include <QWidget>
#include <openssl/x509.h>

/**
 * Macro for adding a new entry to a X509_NAME struct.
 * @param n NID of the entry
 * @param v NULL-byte terminated string
 */
#define certman_X509_NAME_add_entry(n, v) X509_NAME_add_entry_by_NID(name, n, V_ASN1_UTF8STRING, v, -1, -1, 0);

/**
 * Macro for a QLineEdit to add its text automatically as a X509_NAME_ENTRY.
 * The entry is only added when the text is not empty.
 * @param n NID of the entry
 * @param v QLineEdit widget to get value from
 */
#define certman_qt_X509_NAME_add_entry(n, v) { QString text = (v)->text(); \
    if (!text.isEmpty()) X509_NAME_add_entry_by_NID(name, n, V_ASN1_UTF8STRING, (unsigned char *) text.toStdString().c_str(), -1, -1, 0); }

/**
 * Retrieves the value of an entry of the given X509_NAME struct and writes it into the bref buffer
 * @param name the X509_NAME structure to read from
 * @param nid NID of the entry
 * @param bref a char buffer where the value is writto to
 */
#define certman_X509_NAME_get_entry(name, nid, bref) {\
        int length = X509_NAME_get_text_by_NID(name, nid, NULL, 0); \
        X509_NAME_get_text_by_NID(name, nid, bref, length + 1); \
    }

/**
 * Macro for writing the content of an entry of a X509_NAME to a QLineEdit widget
 * @param name the X509_NAME structure to read from
 * @param nid NID of the entry
 * @param v QLineEdit widget to write the value to
 */
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

    /**
     * NameWidget class.
     */
    class NameWidget : public QWidget {
    Q_OBJECT

        /**
         * A X509_NAME structure representing the value of this widget
         */
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

        /**
         * Default constructor of NameWidget.
         * @param parent widget
         */
        explicit NameWidget(QWidget *parent);

        /**
         * NameWidget destructor.
         */
        ~NameWidget();

        /**
         * Generates a X509_NAME structure from the internal fields.
         * @return new X509_NAME structure
         */
        X509_NAME *generateX509Name();

        /**
         * Getter for the value property.
         * @return new X509_NAME structure or NULL if validation failed
         */
        X509_NAME *value();

        /**
         * Setter for the value property.
         * Also sets the internal state and fields to the contents of the X509_NAME structure.
         * @param name existing X509_NAME structure
         */
        void setValue(X509_NAME *name);

        /**
         * Resets the internal fields to their initial state.
         */
        void reset();

    public Q_SLOTS:

        /**
         * Slot for the optional fields checkbox.
         * @param state updated state
         */
        void on_optional_fields_toggle_stateChanged(int state);

        /**
         * Dynamic slot catching any change of internal fields.
         */
        void fieldValueChanged();

    private:

        /**
         * Reference to the Ui factory.
         */
        Ui::NameWidget *ui;

        /**
         * Connects all valueChanged signals of internal fields with fiedlValueChanged slot.
         * @see fieldValueChanged()
         */
        void connectChildrenChangeEvents();

        /**
         * Validates the current state and according to its result renders error messages.
         */
        void renderValidation();

    Q_SIGNALS:

        /**
         * Signal of the value property, emitted when the internal state changed.
         */
        void valueChanged();

    };

}

Q_DECLARE_OPAQUE_POINTER(X509_NAME*);

Q_DECLARE_METATYPE(X509_NAME*);

#endif //NAMEWIDGET_H
