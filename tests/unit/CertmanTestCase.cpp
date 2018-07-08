#include "gtest/gtest.h"
#include <string>
#include <fstream>

#define MSTRINGIZE(s) STRINGIZE(s)
#define STRINGIZE(s) #s

using std::string;
using std::ifstream;
using std::runtime_error;

namespace tests::unit {

    class CertmanTestCase : public testing::Test {
    protected:
        string loadFixture(const string &relativeFixturePath) {
            string path = string(MSTRINGIZE(CERTMAN_TEST_FIXTURES)) + relativeFixturePath;
            ifstream file(path);

            if (!(bool) file) {
                ADD_FAILURE() << "Fixture file \"" + path + "\" does not exist!";
                throw runtime_error("Could not load fixture.");
            }

            return path;
        }
    };
}
