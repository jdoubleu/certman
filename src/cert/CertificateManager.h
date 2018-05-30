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

        void importCertificate(string path);

        void exportCertificate(Certificate *cert, string path);

        CertificateList *getCertificateList();

        void loadCertificates();

        X509 *getX509(string path);

    protected:
        void createKeyPair();

    private:
        CertificateList *certificateList;
    };

}

#endif
