#ifndef KEYPAIRWIDGET_H
#define KEYPAIRWIDGET_H

#include <QWidget>

namespace Ui {
    class KeyPairWidget;
}

namespace gui::widget {

    class KeyPairWidget : public QWidget {
        Q_OBJECT

    public:
        explicit KeyPairWidget(QWidget *parent);

        ~KeyPairWidget() override;

    private:

        Ui::KeyPairWidget *ui;
    };
};


#endif //KEYPAIRWIDGET_H
