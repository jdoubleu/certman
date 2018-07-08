#include "gtest/gtest.h"
#include <src/cert/Certificate.h>
#include <src/cert/CertificateManager.h>

#define STRINGIZE(s) XSTRINGIZE(s)
#define XSTRINGIZE(s) #s
#define FIXTURE(path) string(STRINGIZE(CERTMAN_TEST_FIXTURES)) + string(path)

namespace cert {

    class CertificateTest : public testing::Test {
    protected:
        Certificate *certificate;

        virtual void SetUp() {
            auto *manager = new CertificateManager();
            certificate = new Certificate(manager->getX509(FIXTURE("/certs/test.cer")));
        }

    };

    TEST_F(CertificateTest, NotNull) {
        EXPECT_NE(certificate, nullptr);
    }
}
