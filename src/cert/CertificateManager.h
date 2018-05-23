#include "Certificate.h"

namespace cert {


    struct ImportException {
        string message;
    };

    class CertificateManager {
    public:
        Certificate createCertificate();

        void signCertificate();

        void importCertificate(string path);

        void exportCertificate(X509 *x509, string path, string filename);

    protected:
        void createKeyPair();
    };

}
