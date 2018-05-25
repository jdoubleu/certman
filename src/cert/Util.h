#include <openssl/ossl_typ.h>
#include <string>
#include <ctime>
#include <map>

using std::string;
using std::map;

namespace cert {

    string X509_NAME_to_combined_string(X509_NAME *name);

    map<string, string> X509_NAME_to_map(const X509_NAME *entries);

    time_t ASN1_TIME_to_time(ASN1_TIME *time);

}