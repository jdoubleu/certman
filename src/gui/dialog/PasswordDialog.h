#ifndef PASSWORDDIALOG_H
#define PASSWORDDIALOG_H

#include <QCoreApplication>
#include <QInputDialog>

namespace gui::dialog {

    int passwordCallback(char *buf, int size, int rwflag, void *u);
}

#endif