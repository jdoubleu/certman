#ifndef CERTIFICATEEXTENSION_H
#define CERTIFICATEEXTENSION_H

#include <openssl/x509.h>
#include <string>
#include <map>

using std::string;
using std::map;

namespace cert {

    class CertificateExtension {
    public:
        explicit CertificateExtension(X509_EXTENSION *extension);

        ~CertificateExtension();

        bool critical();

        int typeNID();

        string type();

    private:

        X509_EXTENSION *extension;

        void *value();
    };

}

#endif
