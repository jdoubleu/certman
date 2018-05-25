#include <openssl/ossl_typ.h>
#include <string>
#include <ctime>

using std::string;

namespace cert {

    string X509_NAME_to_combined_string(X509_NAME *name);

    time_t ASN1_TIME_to_time(ASN1_TIME *time);

}