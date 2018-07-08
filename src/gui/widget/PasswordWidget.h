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
        explicit PasswordWidget(QWidget *parent);

        explicit PasswordWidget(QString name, QWidget *parent);

        explicit PasswordWidget(QString name, bool repeat, QWidget *parent);

        explicit PasswordWidget(QString name, QString description, bool repeat, QWidget *parent);

        ~PasswordWidget() override;

        string password();

        BIO *securePassphrase();

        void setName(QString name);

        void setDescription(QString description);

        void setRepeat(bool repeat);

        static QDialog *asDialog(const QString name, const QString description, bool repeat, QWidget *parent = 0);

        static string passwordDialog(const QString name, const QString description, bool repeat, QWidget *parent = 0);

    public Q_SLOTS:

        void on_passwordLineEdit_textChanged(const QString &value);
        void on_repeatPasswordLineEdit_textChanged(const QString &value);

    Q_SIGNALS:

        void passwordChanged();

    private:

        Ui::PasswordWidget *ui;

        QString name;
        QString description;
        bool repeat;

        bool validate();
    };
};


#endif //PASSWORDWIDGET_H
