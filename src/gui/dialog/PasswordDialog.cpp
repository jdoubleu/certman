#include "PasswordDialog.h"

int gui::dialog::passwordCallback(char *buf, int size, int rwflag, void *u) {
    bool ok;
    QString text = QInputDialog::getText(NULL, QCoreApplication::translate("PasswordDialog", "Password"),
                                         QCoreApplication::translate("PasswordDialog", "Password:"),
                                         QLineEdit::Password,
                                         nullptr, &ok);
    if (!ok || text.isEmpty())
        return 0;

    auto len = text.length();
    if (len > size)
        len = size;

    text.toStdString().copy(buf, len, 0);

    return len;
}
