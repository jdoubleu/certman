#ifndef NAMEWIDGETPAGE_H
#define NAMEWIDGETPAGE_H

#include <QWizardPage>

namespace Ui {
    class NameWidgetPage;
}

namespace gui::assistant::page {

    /**
     * Represents the name wizard page.
     */
    class NameWidgetPage : public QWizardPage {
    Q_OBJECT
    public:
        /**
         * Constructor for the wizard page.
         * @param parent Reference to the parent widget.
         */
        explicit NameWidgetPage(QWidget *parent = 0);

        /**
         * Destructor for the widget.
         */
        ~NameWidgetPage();

    private:
        /**
         * Reference to the wizard page ui.
         */
        Ui::NameWidgetPage *ui;
    };
}

#endif //NAMEWIDGETPAGE_H
