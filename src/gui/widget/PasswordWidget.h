#ifndef PASSWORDWIDGET_H
#define PASSWORDWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QString>
#include <string>
#include <openssl/bio.h>

using std::string;

namespace Ui {
    class PasswordWidget;
    class PasswordDialog;
}

namespace gui::widget {

    /**
     * Class represents a passwordWidget.
     */
    class PasswordWidget : public QWidget {
    Q_OBJECT

        Q_PROPERTY(QString name
                           MEMBER
                                   name
                           WRITE
                           setName)
        Q_PROPERTY(QString description
                           MEMBER
                                   description
                           WRITE
                           setDescription)
        Q_PROPERTY(bool repeat
                           MEMBER
                                   repeat
                           WRITE
                           setRepeat)

        Q_PROPERTY(string password
                           READ password
                           NOTIFY passwordChanged
                           DESIGNABLE
                           false
                           SCRIPTABLE
                           false
                           STORED
                           false)

    public:

        /**
         * Constructor for passwordWidget.
         * @param parent Parent QWidget.
         */
        explicit PasswordWidget(QWidget *parent);

        /**
         * Constructor for a passwordWidget.
         * @param name Name for the passwordWidget.
         * @param parent Parent QWidget.
         */
        explicit PasswordWidget(QString name, QWidget *parent);

        /**
         * Constructor for a passwordWidget.
         * @param name Name of the passwordWidget.
         * @param repeat Boolean if needs to be repeated.
         * @param parent Parent QWidget.
         */
        explicit PasswordWidget(QString name, bool repeat, QWidget *parent);

        /**
         * Constructor for a passwordWidget.
         * @param name Name of the passwordWiget.
         * @param description Description of the passwordWidget.
         * @param repeat Boolean if needs to be repeated.
         * @param parent Parent QWidget.
         */
        explicit PasswordWidget(QString name, QString description, bool repeat, QWidget *parent);

        /**
         * Destructor for a passwordWidget.
         */
        ~PasswordWidget() override;

        /**
         * Gets the password.
         * @return The password.
         */
        string password();

        /**
         * Retrieves the password from a secure source.
         * @return BIO containing the password.
         */
        BIO *securePassphrase();

        /**
         * Sets the name.
         * @param name Name to set.
         */
        void setName(QString name);

        /**
         * Set the description.
         * @param description Description to set.
         */
        void setDescription(QString description);

        /**
         * Sets repeat.
         * @param repeat Boolean repeat.
         */
        void setRepeat(bool repeat);

        /**
         * Display the passwordWidget as a dialog.
         * @param name Name of the passwordWidget.
         * @param description Description of the passwordWidget.
         * @param repeat Boolean if needs to be repeated.
         * @param parent Parent QWidget.
         * @return QDialog containing the passwordWidget.
         */
        static QDialog *asDialog(const QString name, const QString description, bool repeat, QWidget *parent = 0);

        /**
         * Blocking passwordDialog if resolved returns the password.
         * @param name Name of the passwordWidget.
         * @param description Description of the passwordWidget.
         * @param repeat Boolean if needs to be repeated.
         * @param parent Parent QWidget.
         * @return The password.
         */
        static string passwordDialog(const QString name, const QString description, bool repeat, QWidget *parent = 0);

        /**
         * Callback function for OpenSSL.
         * @param buf CharBuffer.
         * @param size Size of the buffer.
         * @param rwflag ReadWriteFlag.
         * @param u U.
         * @return Size of password.
         */
        static int asCallbackDialog(char *buf, int size, int rwflag, void *u);

    public Q_SLOTS:

        /**
         * Signal for changeEvent on passwordLine.
         * @param value New input.
         */
        void on_passwordLineEdit_textChanged(const QString &value);

        /**
         * Signal for changeEvent on passwordRepeatLine.
         * @param value New input.
         */
        void on_repeatPasswordLineEdit_textChanged(const QString &value);

    Q_SIGNALS:

        /**
         * PasswordChanged signal.
         */
        void passwordChanged();

    private:

        /**
         * Ui element of the passwordWidget.
         */
        Ui::PasswordWidget *ui;

        /**
         * Name of the passwordWidget.
         */
        QString name;

        /**
         * Description of the passwordWidget.
         */
        QString description;

        /**
         * Repeat password.
         */
        bool repeat;

        /**
         * Validate entries.
         * @return Boolean valid.
         */
        bool validate();
    };
};


#endif //PASSWORDWIDGET_H
