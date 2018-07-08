#include "gtest/gtest.h"
#include <src/cert/CertificateManager.h>

#define STRINGIZE(s) XSTRINGIZE(s)
#define XSTRINGIZE(s) #s
#define FIXTURE(path) string(STRINGIZE(CERTMAN_TEST_FIXTURES)) + string(path)

namespace cert {

    class CertificateManagerTest : public testing::Test {
    protected:
        CertificateManager *crtMgr;

        virtual void SetUp() {
            crtMgr = new CertificateManager();
        }

    };

    TEST_F(CertificateManagerTest, GetX509NotNull) {
        EXPECT_NE(crtMgr->getX509(FIXTURE("/certs/test.cer")), nullptr);

    }

    TEST_F(CertificateManagerTest, GetKeyNotNull) {
        EXPECT_NE(crtMgr->getKey(FIXTURE("/certs/test_key.pem")), nullptr);
    }

    TEST_F(CertificateManagerTest, GetCertificateListAsX509StoreTest) {
        EXPECT_EQ(typeid(X509_STORE_new()), typeid(crtMgr->getCertificateListAsX509Store()));
    }

    TEST_F(CertificateManagerTest, GenerateKeyUsageExtensionsNotNull) {
        EXPECT_NE(crtMgr->generateKeyUsageExtensions(false, false, false,
                                                     false, false,
                                                     false, false, false,
                                                     false, false), nullptr);
    }

}
