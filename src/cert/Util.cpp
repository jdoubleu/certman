#include <openssl/bio.h>
#include <openssl/x509.h>
#include <cstring>
#include "Util.h"

string cert::x509NameAsString(X509_NAME *name) {
    BIO *out = BIO_new(BIO_s_mem());
    BUF_MEM *buffer;
    X509_NAME_print(out, name, 0);
    BIO_get_mem_ptr(out, &buffer);
    string result = string(buffer->data, buffer->length);
    BIO_free(out);
    return result;
}

time_t cert::ASN1_GetTimeT(ASN1_TIME *time) {
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
