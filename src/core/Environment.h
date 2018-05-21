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
            return QStandardPaths::locate(
                    QStandardPaths::AppDataLocation,
                    QString::fromStdString("certman"),
                    QStandardPaths::LocateDirectory
            ).toStdString();
        }

        static string getCertificatesDir() {
            return Environment::getAppDataLocation() + "certs";
        }
    };

}
