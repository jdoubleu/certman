#ifndef PASSWORDWIDGET_H
#define PASSWORDWIDGET_H

#include <QWidget>
#include <QString>

namespace Ui {
    class PasswordWidget;
}

namespace gui::widget {

    class PasswordWidget: public QWidget {
    Q_OBJECT

    public:
        explicit PasswordWidget(QString name, QWidget *parent);
        explicit PasswordWidget(QString name, QString description, QWidget *parent);

        ~PasswordWidget() override;

    private:

        Ui::PasswordWidget *ui;

        QString name;
        QString description;
    };
};


#endif //PASSWORDWIDGET_H
