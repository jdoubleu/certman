#include <QDialog>

namespace Ui {
    class ImportAssistant;
}

namespace gui::assistant {

    class ImportAssistant : public QDialog {
    Q_OBJECT

    public:
        explicit ImportAssistant(QWidget *parent = 0);

        ~ImportAssistant();

    private:
        Ui::ImportAssistant *ui;

    private slots:
        void chooseFile();
        void submit();
    };

}
