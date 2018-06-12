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
