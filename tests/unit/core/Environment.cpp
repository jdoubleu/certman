#include "gtest/gtest.h"
#include "../CertmanTestCase.cpp"
#include <src/core/Environment.h>

using core::Environment;

namespace tests::unit {

    class EnvironmentTest : public CertmanTestCase {};

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
