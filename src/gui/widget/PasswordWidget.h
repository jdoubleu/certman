#ifndef PASSWORDWIDGET_H
#define PASSWORDWIDGET_H

#include <QWidget>
#include <QString>
#include <string>
#include <openssl/bio.h>

using std::string;

namespace Ui {
    class PasswordWidget;
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

    public:
        explicit PasswordWidget(QWidget *parent);

        explicit PasswordWidget(QString name, QWidget *parent);

        explicit PasswordWidget(QString name, bool repeat, QWidget *parent);

        explicit PasswordWidget(QString name, QString description, bool repeat, QWidget *parent);

        ~PasswordWidget() override;

        bool validate();

        string password();

        BIO *securePassphrase();

        void setName(QString name);

        void setDescription(QString description);

        void setRepeat(bool repeat);

    private:

        Ui::PasswordWidget *ui;

        QString name;
        QString description;
        bool repeat;
    };
};


#endif //PASSWORDWIDGET_H
