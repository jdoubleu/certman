#include "Certificate.h"

using std::vector;

namespace cert {


    struct ImportException {
        string message;
    };

    class CertificateManager {
    public:
        CertificateManager();

        Certificate createCertificate();

        void signCertificate();

        void importCertificate(string path);

        void exportCertificate(X509 *x509, string path, string filename);

        vector<Certificate> *getCertificateList();

        void loadCertificates();

        X509 *getX509(string path);

    protected:
        void createKeyPair();

    private:
        vector<Certificate> *certificateList;

    };

}
