#include "gtest/gtest.h"
#include <src/cert/CertificateList.h>
#include <src/cert/Certificate.h>
#include <src/cert/CertificateManager.h>

#define STRINGIZE(s) XSTRINGIZE(s)
#define XSTRINGIZE(s) #s
#define FIXTURE(path) string(STRINGIZE(CERTMAN_TEST_FIXTURES)) + string(path)

namespace cert {

    class CertificateListTest : public testing::Test {
    protected:
        CertificateManager *crtMgr;
        Certificate *cert;
        CertificateList *certificateList;

        virtual void SetUp() {
            crtMgr = new CertificateManager();
            cert = new Certificate(crtMgr->getX509(FIXTURE("/certs/test.cer")));
            certificateList = new CertificateList();
        }

    };

    TEST_F(CertificateListTest,Add) {
        certificateList->add(cert);
        EXPECT_EQ(certificateList->listAll()->size(),1);
    }

    TEST_F(CertificateListTest,Remove) {
        certificateList->add(cert);
        certificateList->remove(cert);
        EXPECT_EQ(certificateList->listAll()->size(),0);
    }

    TEST_F(CertificateListTest, NoDuplicates) {
        certificateList->add(cert);
        certificateList->add(cert);
        EXPECT_EQ(certificateList->listAll()->size(),1);
    }

}
