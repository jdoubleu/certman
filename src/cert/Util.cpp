#include <openssl/bio.h>
#include <openssl/x509.h>
#include <cstring>
#include "Util.h"

using std::pair;

string cert::X509_NAME_to_combined_string(X509_NAME *name) {
    BIO *out = BIO_new(BIO_s_mem());
    BUF_MEM *buffer;
    X509_NAME_print(out, name, 0);
    BIO_get_mem_ptr(out, &buffer);
    string result = string(buffer->data, buffer->length);
    BIO_free(out);
    return result;
}

time_t cert::ASN1_TIME_to_time(ASN1_TIME *time) {
    struct tm t{};
    const auto *str = (const char *) time->data;
    size_t i = 0;

    memset(&t, 0, sizeof(t));

    if (time->type == V_ASN1_UTCTIME) {
        t.tm_year = (str[i++] - '0') * 10 + (str[++i] - '0');
        if (t.tm_year < 70)
            t.tm_year += 100;
    } else if (time->type == V_ASN1_GENERALIZEDTIME) {
        t.tm_year = (str[i++] - '0') * 1000 + (str[++i] - '0') * 100 + (str[++i] - '0') * 10 + (str[++i] - '0');
        t.tm_year -= 1900;
    }
    t.tm_mon = ((str[i++] - '0') * 10 + (str[++i] - '0')) - 1;
    t.tm_mday = (str[i++] - '0') * 10 + (str[++i] - '0');
    t.tm_hour = (str[i++] - '0') * 10 + (str[++i] - '0');
    t.tm_min = (str[i++] - '0') * 10 + (str[++i] - '0');
    t.tm_sec = (str[i++] - '0') * 10 + (str[++i] - '0');

    return mktime(&t);
}

map<string, string> cert::X509_NAME_to_map(const X509_NAME *entries, enum X509_NAME_map_key_type type) {
    map<string, string> fields;

    for (int i = 0; i < X509_NAME_entry_count(entries); i++) {
        X509_NAME_ENTRY *entry = X509_NAME_get_entry(entries, i);
        ASN1_OBJECT *field = X509_NAME_ENTRY_get_object(entry);
        ASN1_STRING *value = X509_NAME_ENTRY_get_data(entry);

        int fieldNID = OBJ_obj2nid(field);
        string fieldName = type == LONG ? OBJ_nid2ln(fieldNID) : OBJ_nid2sn(fieldNID);
        string fieldValue = string((char *) ASN1_STRING_get0_data(value));

        fields.insert(pair<string,string>(fieldName, fieldValue));
    }

    return fields;
};

map<int, string> cert::X509_NAME_to_map_NID(const X509_NAME *entries) {
    map<int, string> fields;

    for (int i = 0; i < X509_NAME_entry_count(entries); i++) {
        X509_NAME_ENTRY *entry = X509_NAME_get_entry(entries, i);
        ASN1_OBJECT *field = X509_NAME_ENTRY_get_object(entry);
        ASN1_STRING *value = X509_NAME_ENTRY_get_data(entry);

        int fieldNID = OBJ_obj2nid(field);
        string fieldValue = string((char *) ASN1_STRING_get0_data(value));

        fields.insert(pair<int,string>(fieldNID, fieldValue));
    }

    return fields;
};