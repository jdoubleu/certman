#include "gtest/gtest.h"
#include <src/cert/Certificate.h>
#include <src/cert/CertificateManager.h>
#include <src/cert/CertificateExtension.h>

#define STRINGIZE(s) XSTRINGIZE(s)
#define XSTRINGIZE(s) #s
#define FIXTURE(path) string(STRINGIZE(CERTMAN_TEST_FIXTURES)) + string(path)

namespace cert {

    class CertificateExtensionTest : public testing::Test {
    protected:
        vector<CertificateExtension *> extenstion;

        virtual void SetUp() {
            auto *manager = new CertificateManager();
            auto *certificate = new Certificate(manager->getX509(FIXTURE("/certs/ca1/certs/ca.pem")));
            extenstion = certificate->getExtensions();
        }

    };

    TEST_F(CertificateExtensionTest, ExtensionsExists) {
        EXPECT_EQ(extenstion.size(), 4);
    }
}
