#include <QDir>
#include <QStandardPaths>
#include "Environment.h"

OS Environment::getOS() {
    #ifdef _WIN64
        return WINDOWS;
    #elif __APPLE__ || __MACH__
        return MACOS;
    #elif __linux__
        return LINUX;
    #endif
}

string Environment::getHomeDir() {
    return QDir::homePath().toStdString();
}

string Environment::getAppDataLocation() {
    return QStandardPaths::locate(QStandardPaths::StandardLocation::AppDataLocation, QString::fromStdString("certman")).toStdString();
}