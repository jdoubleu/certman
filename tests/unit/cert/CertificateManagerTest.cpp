#include "gtest/gtest.h"
#include "../CertmanTestCase.cpp"
#include <src/cert/CertificateManager.h>

using cert::CertificateManager;

namespace tests::unit {

    class CertificateManagerTest : public CertmanTestCase {
    protected:
        CertificateManager *crtMgr;

        virtual void SetUp() {
            crtMgr = new CertificateManager();
        }

    };

    TEST_F(CertificateManagerTest, GetX509NotNull) {
        EXPECT_NE(crtMgr->getX509(loadFixture("/certs/test.cer")), nullptr);

    }

    TEST_F(CertificateManagerTest, GetKeyNotNull) {
        EXPECT_NE(crtMgr->getKey(loadFixture("/certs/test_key.pem")), nullptr);
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
