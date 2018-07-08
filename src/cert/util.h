#ifndef UTIL_H
#define UTIL_H

#include <openssl/ossl_typ.h>
#include <string>
#include <ctime>
#include <map>

using std::string;
using std::map;

namespace cert {

    /**
     * Variants of X509 key type.
     */
    enum X509_NAME_map_key_type {
        LONG,
        SHORT
    };

    /**
     * Get String from X509_NAME structure.
     * @param name X509_NAME structure.
     * @return Formatted X509_NAME.
     */
    string X509_NAME_to_combined_string(X509_NAME *name);

    /**
     * Converts X509_NAME entries to string map.
     * @param entries X509_NAME element.
     * @param type Variants of the conversion.
     * @return Title and content.
     */
    map<string, string> X509_NAME_to_map(const X509_NAME *entries, enum X509_NAME_map_key_type type = LONG);

    /**
     * Converts X509_NAME entries to nid map.
     * @param entries X509_NAME element.
     * @return NID and content.
     */
    map<int, string> X509_NAME_to_map_NID(const X509_NAME *entries);

    /**
     * Get the specific field of a X509_NAME.
     * @param name X509_NAME element.
     * @param field Name of the field to be returned.
     * @return Content of the field.
     */
    string X509_NAME_get_field(X509_NAME *name, const string field);

    /**
     * Converts ASN1_TIME to time_t.
     * @param time ANS1_TIME object.
     * @return Converted time_t.
     */
    time_t ASN1_TIME_to_time(ASN1_TIME *time);

    /**
     * Transform time_t to readable string.
     * @param _tm time_t to be transformed.
     * @return Human readable time.
     */
    string time_to_string(time_t _tm);

    /**
     * Sanitize string to be compatible with filesystem limitation.
     * @param s Reference to string.
     */
    void removeChars(string *s);
}

#endif
