#ifndef CERTIFICATEMANAGER_H
#define CERTIFICATEMANAGER_H

#include "Certificate.h"
#include "CertificateList.h"

using std::vector;

namespace cert {

    class CertificateManager {
    public:
        CertificateManager();

        bool removeCertifcate(Certificate *cert);

        void signCertificate();

        void importCertificate(string pathCert, string pathPrivateKey);

        void exportCertificate(Certificate *cert, string path);

        void exportPrivateKeyFile(string origin, string destination);

        void exportPrivateKey(EVP_PKEY *pkey, string location);

        CertificateList *getCertificateList();

        void loadCertificates();

        X509 *getX509(string path);

        EVP_PKEY *getKey(string path);

        bool hasPrivateKey(Certificate *cert);

        string getCertificateDefaultLocation(Certificate *cert);

        string getPrivateKeyDefaultLocation(Certificate *cert);

        bool createCertificate(int algorithm, int keySize, int validityDays, X509_NAME *subjectName,
                               X509_NAME *issuerName);

    protected:
        void createKeyPair();

    private:
        CertificateList *certificateList;
    };

}

#endif
