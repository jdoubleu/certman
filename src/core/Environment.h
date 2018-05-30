#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#include <QDir>
#include <QStandardPaths>

using std::string;

namespace core {

    enum OS {
        LINUX,
        MACOS,
        WINDOWS
    };

    class Environment {
    public:
        static OS getOS();

        static string getHomeDir();

        static string getAppDataLocation();

        static string getCertificatesDir();
    };

}

#endif
