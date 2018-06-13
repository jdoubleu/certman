#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#include <list>
#include <QDir>
#include <QStandardPaths>

using std::string;
using std::list;

namespace core {

    class Environment {
    public:

        static string getHomeDir();

        static string getAppDataLocation();

        static string getCertificatesDir();

        static string iso3166_alpha2_codes[];

        static list<string> iso3166_alpha2_codes_list;
    };

}

#endif
