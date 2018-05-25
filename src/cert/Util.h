#include <openssl/ossl_typ.h>
#include <string>
#include <ctime>

using std::string;

namespace cert {

    string x509NameAsString(X509_NAME *name);

    time_t ASN1_GetTimeT(ASN1_TIME *time);

}