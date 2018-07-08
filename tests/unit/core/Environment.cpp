#include "gtest/gtest.h"
#include <src/core/Environment.h>

namespace core {

    class EnvironmentTest : public testing::Test {};

    TEST_F(EnvironmentTest, CertificatesDirNotNull) {
        EXPECT_GT(Environment::getCertificatesDir().size(), 1);
    }

    TEST_F(EnvironmentTest, AppDataLocationNotNull) {
        EXPECT_GT(Environment::getAppDataLocation().size(), 1);
    }

    TEST_F(EnvironmentTest, HomeDirNotNull) {
        EXPECT_GT(Environment::getHomeDir().size(), 1);
    }
}
