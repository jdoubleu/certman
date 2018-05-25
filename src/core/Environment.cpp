#include "Environment.h"

string core::Environment::getCertificatesDir() {
    QDir dir(QString::fromStdString(Environment::getAppDataLocation() + "/certs"));
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    return dir.absolutePath().toStdString();
}

string core::Environment::getAppDataLocation() {
    QDir dir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    return dir.absolutePath().toStdString();
}

string core::Environment::getHomeDir() {
    return QDir::homePath().toStdString();
}

core::OS core::Environment::getOS() {
#ifdef _WIN64
    return WINDOWS;
#elif __APPLE__ || __MACH__
    return MACOS;
#elif __linux__
    return LINUX;
#endif
}
