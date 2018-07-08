#include "gtest/gtest.h"
#include "../CertmanTestCase.cpp"
#include <src/cert/util.h>
#include <src/cert/CertificateManager.h>

using cert::CertificateManager;
using cert::Certificate;

namespace tests::unit {

    class UtilTest : public CertmanTestCase {
    protected:
        CertificateManager *crtMgr;
        Certificate *cert;

        virtual void SetUp() {
            crtMgr = new CertificateManager();
            cert = new Certificate(crtMgr->getX509(loadFixture("/certs/test.cer")));
        }

    };

    TEST_F(UtilTest, X509NameToCombinedStringTest) {
        EXPECT_EQ(cert::X509_NAME_to_combined_string(X509_get_issuer_name(cert->getX509())),
                  "CN=*.test.com, O=dollor, OU=sit, C=US, L=ipsum, ST=lorem");
    }

    TEST_F(UtilTest, ASN1_TIME_to_time) {
        auto time = cert::ASN1_TIME_to_time(X509_get_notBefore(cert->getX509()));
        time_t t;
        EXPECT_EQ(typeid(time), typeid(t));
    }

    TEST_F(UtilTest, TimeToString) {
        auto time = cert::ASN1_TIME_to_time(X509_get_notBefore(cert->getX509()));
        auto timeString = cert::time_to_string(time);
        std::string testString = "string";
        EXPECT_EQ(typeid(timeString), typeid(testString));
    }

    TEST_F(UtilTest, RemoveChars) {
        string illegal = "*.test.com";
        cert::removeChars(&illegal);
        EXPECT_EQ(illegal, "testcom");
    }
}
