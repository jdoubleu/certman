#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#include <list>
#include <QDir>
#include <QStandardPaths>

using std::string;
using std::list;

namespace core {

    /**
     * Contains environment methods.
     */
    class Environment {
    public:

        /**
         * Get the home directory.
         * @return Path to home directory.
         */
        static string getHomeDir();

        /**
         * Get the application data directory.
         * @return Path to application data directory.
         */
        static string getAppDataLocation();

        /**
         * Get the internal certificate directory.
         * @return Path to certificate directory.
         */
        static string getCertificatesDir();

        /**
         * Array of ISO3166 alpha codes.
         */
        static string iso3166_alpha2_codes[];

        /**
         * List of ISO3166 alpha codes.
         */
        static list<string> iso3166_alpha2_codes_list;
    };

}

#endif
