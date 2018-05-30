#ifndef CERTIFICATE_H
#define CERTIFICATE_H

#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <string>
#include <openssl/ossl_typ.h>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

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

        bool operator==(const Certificate &c);

    private:
        X509 *certificate;
    };

}

#endif
