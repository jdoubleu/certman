#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

namespace gui::window {

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    void setupActions();

private slots:
    void importCertificate();
};

}