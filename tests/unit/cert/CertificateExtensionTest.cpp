#include "gtest/gtest.h"
#include "../CertmanTestCase.cpp"
#include <src/cert/Certificate.h>
#include <src/cert/CertificateManager.h>
#include <src/cert/CertificateExtension.h>

using cert::CertificateManager;
using cert::Certificate;
using cert::CertificateExtension;

namespace tests::unit {

    typedef struct {
        string fixture;
        int index;
        int expectedNIDType;
        string expectedTypeString;
        string expectedContent;
        bool isCritical;
    } CertificateExtensionTestParameter;

    class CertificateExtensionTest
            : public CertmanTestCase, public ::testing::WithParamInterface<CertificateExtensionTestParameter> {
    public:
        virtual void SetUp() {
            parameter = GetParam();

            auto *certificate = new Certificate((new CertificateManager())->getX509(loadFixture(parameter.fixture)));
            extension = certificate->getExtensions()[parameter.index];
        }

        virtual void TearDown() {
            parameter = {};
            delete extension;
            extension = NULL;
        }

    protected:
        CertificateExtensionTestParameter parameter;
        CertificateExtension *extension;
    };

    TEST_P(CertificateExtensionTest, HasCorrectNIDType) {
        EXPECT_EQ(extension->typeNID(), parameter.expectedNIDType);
    }

    TEST_P(CertificateExtensionTest, HasCorrectTypeString) {
        EXPECT_STREQ(extension->type().c_str(), parameter.expectedTypeString.c_str());
    }

    TEST_P(CertificateExtensionTest, ProducesCorrentContentString) {
        EXPECT_STREQ(extension->sprint().c_str(), parameter.expectedContent.c_str());
    }

    TEST_P(CertificateExtensionTest, HasCorrectCriticalFlag) {
        EXPECT_EQ(extension->critical(), parameter.isCritical);
    }

    /**
     * Test parameters/fixture generator
     * @return
     */
    std::vector<CertificateExtensionTestParameter> ParametersGenerator() {
        const char *fixture1 = "/certs/ca1/certs/ca.pem";

        return {
                {
                        fixture1,
                        0,
                        NID_subject_key_identifier,
                        "X509v3 Subject Key Identifier",
                        "74:03:56:59:2E:A8:B7:F6:CF:CF:C6:DC:4F:46:A2:33:60:23:5D:2A",
                        false
                },
                {
                        fixture1,
                        1,
                        NID_authority_key_identifier,
                        "X509v3 Authority Key Identifier",
                        "keyid:74:03:56:59:2E:A8:B7:F6:CF:CF:C6:DC:4F:46:A2:33:60:23:5D:2A\n",
                        false
                },
                {
                        fixture1,
                        2,
                        NID_basic_constraints,
                        "X509v3 Basic Constraints",
                        "CA:TRUE",
                        true
                },
                {
                        fixture1,
                        3,
                        NID_key_usage,
                        "X509v3 Key Usage",
                        "Digital Signature, Certificate Sign",
                        true
                }
        };
    }

    INSTANTIATE_TEST_CASE_P(CertificateExtensionTest, CertificateExtensionTest,
                            ::testing::ValuesIn(ParametersGenerator()));
}
