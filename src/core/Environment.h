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
        static OS getOS() {
#ifdef _WIN64
            return WINDOWS;
#elif __APPLE__ || __MACH__
            return MACOS;
#elif __linux__
            return LINUX;
#endif
        }

        static string getHomeDir() {
            return QDir::homePath().toStdString();
        }

        static string getAppDataLocation() {
            QDir dir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
            if (!dir.exists()) {
                dir.mkpath(".");
            }
            return dir.absolutePath().toStdString();
        }

        static string getCertificatesDir() {
            QDir dir(QString::fromStdString(Environment::getAppDataLocation() + "/certs"));
            if (!dir.exists()) {
                dir.mkpath(".");
            }
            return dir.absolutePath().toStdString();
        }
    };

}
