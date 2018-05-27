#include <openssl/ossl_typ.h>
#include <string>
#include <ctime>
#include <map>

using std::string;
using std::map;

namespace cert {

    enum X509_NAME_map_key_type {
        LONG,
        SHORT
    };

    string X509_NAME_to_combined_string(X509_NAME *name);

    map<string, string> X509_NAME_to_map(const X509_NAME *entries, enum X509_NAME_map_key_type type = LONG);

    map<int, string> X509_NAME_to_map_NID(const X509_NAME *entries);

    string X509_NAME_get_field(X509_NAME *name, const string field);

    time_t ASN1_TIME_to_time(ASN1_TIME *time);

    string time_to_string(time_t _tm);
}