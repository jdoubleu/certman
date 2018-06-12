#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#include <QDir>
#include <QStandardPaths>

using std::string;

namespace core {

    class Environment {
    public:

        static string getHomeDir();

        static string getAppDataLocation();

        static string getCertificatesDir();
    };

}

#endif
