#ifndef CERTIFICATEMANAGER_H
#define CERTIFICATEMANAGER_H

#include <QtCore>
#include "Certificate.h"
#include "CertificateList.h"

using std::vector;

namespace cert {

    typedef std::function<void(BIO *sink)> EXPORT_PRIVATEKEY_FUNC;

    typedef struct {
        EVP_PKEY *keyPair;
        EXPORT_PRIVATEKEY_FUNC exportFunc;
    } KEYPAIR_EXPORT;

    typedef struct {
        Certificate *certificate;
        KEYPAIR_EXPORT keyPairExport;
    } CERT_EXPORT;

    class CertificateManager {
    Q_DECLARE_TR_FUNCTIONS(CertificateManager)

    public:
        CertificateManager();

        bool removeCertifcate(Certificate *cert);

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

        Certificate *createCertificate(X509_NAME *subject, X509_NAME *issuer, int validityDays, EVP_PKEY *keyPair,
                                       const EVP_MD *signMd, long serialNumber = 1);

        Certificate *createCertificate(X509_NAME *subject, X509_NAME *issuer, int validityDays, EVP_PKEY *keyPair,
                                       long serialNumber = 1);

        X509_STORE *getCertificateListAsX509Store();

        bool signCertificate(Certificate *cert, EVP_PKEY *pKey, X509_NAME *issuer);

        EVP_PKEY *generateKeyPair(int algorithm, int keySize);

        void importNewCertificate(CERT_EXPORT newCertificate);

    private:
        CertificateList *certificateList;
    };

}

#endif
