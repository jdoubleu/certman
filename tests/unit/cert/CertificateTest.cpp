#include "gtest/gtest.h"
#include "../CertmanTestCase.cpp"
#include <src/cert/Certificate.h>
#include <src/cert/CertificateManager.h>

using cert::CertificateManager;
using cert::Certificate;

namespace tests::unit {

    class CertificateTest : public CertmanTestCase {
    protected:
        CertificateManager *manager;
        Certificate *certificate;

        virtual void SetUp() {
            manager = new CertificateManager();
            certificate = new Certificate(manager->getX509(loadFixture("/certs/test.cer")));
        }

    };

    TEST_F(CertificateTest, X509NotNull) {
        EXPECT_NE(certificate->getX509(), nullptr);
    }

    TEST_F(CertificateTest, VersionEquals) {
        EXPECT_EQ(certificate->getVersion(), 2);
    }

    TEST_F(CertificateTest, ThumbprintEquals) {
        EXPECT_EQ(certificate->getThumbprint(), "04E8CC4D1CC396CDD3E609EEF9961D8044FCE35D");
    }

    TEST_F(CertificateTest, IssuerEquals) {
        EXPECT_EQ(certificate->getIssuer(), "CN=*.test.com, O=dollor, OU=sit, C=US, L=ipsum, ST=lorem");
    }

    TEST_F(CertificateTest, SubjectEquals) {
        EXPECT_EQ(certificate->getSubject(), "CN=*.test.com, O=dollor, OU=sit, C=US, L=ipsum, ST=lorem");
    }

    TEST_F(CertificateTest, KeyTypeEquals) {
        EXPECT_EQ(certificate->getKeyType(), "rsa");
    }

    TEST_F(CertificateTest, KeySizeEquals) {
        EXPECT_EQ(certificate->getKeySize(), 256);
    }

    TEST_F(CertificateTest, HasExtensions) {
        auto *certificate = new Certificate(manager->getX509(loadFixture("/certs/ca1/certs/ca.pem")));

        EXPECT_EQ(certificate->getExtensions().size(), 4);
    }
}
