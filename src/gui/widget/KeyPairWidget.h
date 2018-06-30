#ifndef KEYPAIRWIDGET_H
#define KEYPAIRWIDGET_H

#include <QWidget>
#include <openssl/evp.h>

namespace Ui {
    class KeyPairWidget;
}

namespace gui::widget {

    struct algorithmComboBox_field_st {
        const char *name;
        const int algorithm;
    };

    typedef struct algorithmComboBox_field_st SUPPORTED_KEY_ALG;

    struct wrappingAlgorithmComboBox_field_st {
        const char *name;
        const EVP_CIPHER *cipher;
    };

    typedef struct wrappingAlgorithmComboBox_field_st SUPPORTED_WRAPPING_ALG;

    class KeyPairWidget : public QWidget {
        Q_OBJECT

    public:
        explicit KeyPairWidget(QWidget *parent);

        ~KeyPairWidget() override;

        bool validate();

    public Q_SLOTS:

        void on_wrappingAlgorithmComboBox_currentIndexChanged(int index);

    private:

        Ui::KeyPairWidget *ui;

        void addSupportedKeyAlgorithms();

        void addSupportedKeyWrappingAlgorithms();
    };

};

Q_DECLARE_METATYPE(gui::widget::SUPPORTED_WRAPPING_ALG);

#endif //KEYPAIRWIDGET_H
