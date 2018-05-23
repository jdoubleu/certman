#include <openssl/ossl_typ.h>
#include <string>
#include <ctime>

using std::string;

namespace cert {
    class Util {
    public:
        static string x509NameAsString(X509_NAME *name);

        static time_t ASN1_GetTimeT(ASN1_TIME* time);
    };
}