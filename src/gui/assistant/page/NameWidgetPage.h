#ifndef NAMEWIDGETPAGE_H
#define NAMEWIDGETPAGE_H

#include <QWizardPage>

namespace Ui {
    class NameWidgetPage;
}

namespace gui::assistant::page {
    class NameWidgetPage : public QWizardPage {
    Q_OBJECT
    public:
        explicit NameWidgetPage(QWidget *parent = 0);

        ~NameWidgetPage();

    private:
        Ui::NameWidgetPage *ui;
    };
}

#endif //NAMEWIDGETPAGE_H
