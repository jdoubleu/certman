#include <string>

using namespace std;

enum OS {
    LINUX,
    MACOS,
    WINDOWS
};

class Environment {
public:
    OS getOS();
    string getHomeDir();
    string getAppDataLocation();
    string getCertificatesDir() {
        return this->getAppDataLocation() + "certs";
    }
};
