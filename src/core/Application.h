#include "../cert/CertificateManager.h"
#include "Environment.h"

using cert::CertificateManager;
using core::Environment;

namespace core {

    class Application {
    public:
        Application();

        ~Application();

        int run(int argc, char *argv[]);

    private:
        CertificateManager *crtMgr;
        Environment *env;
    };

}
