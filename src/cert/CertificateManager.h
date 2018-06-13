#ifndef CERTIFICATEMANAGER_H
#define CERTIFICATEMANAGER_H

#include "Certificate.h"
#include "CertificateList.h"

using std::vector;

namespace cert {

    class CertificateManager {
    public:
        CertificateManager();

        Certificate createCertificate();

        void signCertificate();

        void importCertificate(string pathCert, string pathPrivateKey);

        void exportCertificate(Certificate *cert, string path);

        CertificateList *getCertificateList();

        void loadCertificates();

        X509 *getX509(string path);

        EVP_PKEY *getKey(string path);

        bool hasPrivateKey(Certificate *cert);

        void exportPrivateKey(EVP_PKEY *pkey, string destination);

        string getCertificateDefaultLocation(Certificate *cert);

        string getPrivateKeyDefaultLocation(Certificate *cert);

    protected:
        void createKeyPair();

    private:
        CertificateList *certificateList;

        void exportPrivateKey(string origin, string destination);



    };

}

#endif
