#ifndef APPLICATION_H
#define APPLICATION_H

#include "../cert/CertificateManager.h"
#include "Environment.h"

using cert::CertificateManager;
using core::Environment;

namespace core {

    /**
     * Represents the Qt Application.
     */
    class Application {
    public:
        /**
         * Default constructor for initialization.
         */
        Application();

        /**
         * Destructor for cleaning up.
         */
        ~Application();

        /**
         * Starts the application.
         * @param argc Number of arguments.
         * @param argv Vector of arguments.
         * @return Exit code.
         */
        int run(int argc, char *argv[]);

    private:
        /**
         * Global certificate manger instance.
         */
        CertificateManager *crtMgr;
    };

}

#endif
