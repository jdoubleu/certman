#include "Certificate.h"

namespace cert {

    class CertificateManager {
    public:
        Certificate createCertificate();

        void signCertificate();

        void importCertificate();

        void exportCertificate();

    protected:
        void createKeyPair();
    };

}
