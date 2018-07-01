#ifndef CERTIFICATE_H
#define CERTIFICATE_H

#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <string>
#include <openssl/ossl_typ.h>
#include <vector>
#include <map>
#include <QtGui>
#include "CertificateExtension.h"

using std::string;
using std::vector;
using std::map;
using cert::CertificateExtension;

namespace cert {

    class Certificate {
    public:
        explicit Certificate(X509 *certificate);

        X509 *getX509();

        long getVersion();

        string getThumbprint() const;

        string getIssuer();

        map<string, string> getIssuerFields();

        string getIssuerField(const string field);

        string getSubject();

        map<string, string> getSubjectFields();

        string getSubjectField(const string field);

        string getSignatureAlgorithm();

        string getKeyType();

        int getKeySize();

        time_t getCreated();

        time_t getExpires();

        vector<string> getASN();

        vector<CertificateExtension *> getExtensions();

        int sign(EVP_PKEY *pKey);

        void addBasicConstraints(bool ca, int pathLen);

        void addKeyUsage(bool critical, bool digitalSignature = false, bool nonRepudation = false,
                         bool keyEncipherment = false,
                         bool dataEncipherment = false, bool keyAgreement = false, bool keyCertSign = false,
                         bool cRLSign = false, bool encipherOnly = false,
                         bool decipherOnly = false);

        bool operator==(const Certificate &c);

    private:
        X509 *certificate;

    };

    struct CertificateContainer {
        Certificate *certificate;
    };
}

Q_DECLARE_METATYPE(cert::CertificateContainer);

#endif
