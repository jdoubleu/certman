#ifndef CERTIFICATE_H
#define CERTIFICATE_H

#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <string>
#include <openssl/ossl_typ.h>
#include <vector>

using std::string;
using std::vector;

namespace cert {

    class Certificate {
    public:
        explicit Certificate(X509 *certificate);

        X509 *getX509();

        long getVersion();

        string getThumbprint() const;

        string getIssuer();

        string getSubject();

        string getSignatureAlgorithm();

        string getKeyType();

        int getKeySize();

        time_t getCreated();

        time_t getExpires();

        X509_NAME *getSubjectNAME();

        X509_NAME *getIssuerNAME();

        vector<string> getASN();

        bool operator==(const Certificate &c);

    private:
        X509 *certificate;
    };

}

#endif