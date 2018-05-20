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
    string getExecutionDir();
    string getApplicationDir();
};
