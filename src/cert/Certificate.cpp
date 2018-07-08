#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <sstream>
#include "Certificate.h"
#include "util.h"

using std::stringstream;
using std::vector;

using namespace cert;

Certificate::Certificate(X509 *certificate) {
    this->certificate = certificate;
}

X509 *Certificate::getX509() {
    return this->certificate;
}

long Certificate::getVersion() {
    return X509_get_version(this->certificate);
}

string Certificate::getThumbprint() const {
    static const char hexbytes[] = "0123456789ABCDEF";
    unsigned int messageDigest_size;
    unsigned char messageDigest[EVP_MAX_MD_SIZE];
    const EVP_MD *digest = EVP_get_digestbyname("sha1");
    X509_digest(this->certificate, digest, messageDigest, &messageDigest_size);
    stringstream toHex;
    for (int pos = 0; pos < messageDigest_size; pos++) {
        toHex << hexbytes[(messageDigest[pos] & 0xf0) >> 4];
        toHex << hexbytes[(messageDigest[pos] & 0x0f) >> 0];
    }
    return toHex.str();
}

string Certificate::getIssuer() {
    return X509_NAME_to_combined_string(X509_get_issuer_name(this->certificate));
}

map<string, string> Certificate::getIssuerFields() {
    return X509_NAME_to_map(X509_get_issuer_name(this->certificate));
};

string Certificate::getIssuerField(const string field) {
    return X509_NAME_get_field(X509_get_issuer_name(this->certificate), field);
};

string Certificate::getSubject() {
    return X509_NAME_to_combined_string(X509_get_subject_name(this->certificate));
}

map<string, string> Certificate::getSubjectFields() {
    return X509_NAME_to_map(X509_get_subject_name(this->certificate));
};

string Certificate::getSubjectField(const string field) {
    return X509_NAME_get_field(X509_get_subject_name(this->certificate), field);
}

string Certificate::getKeyType() {
    EVP_PKEY *pkey = X509_get_pubkey(this->certificate);
    int key_type = EVP_PKEY_id(pkey);
    EVP_PKEY_free(pkey);
    if (key_type == EVP_PKEY_RSA) return "rsa";
    if (key_type == EVP_PKEY_DSA) return "dsa";
    if (key_type == EVP_PKEY_DH) return "dh";
    if (key_type == EVP_PKEY_EC) return "ecc";
    return "";
}

int Certificate::getKeySize() {
    EVP_PKEY *pkey = X509_get_pubkey(this->certificate);
    int keysize = EVP_PKEY_size(pkey);
    EVP_PKEY_free(pkey);
    return keysize;
}

time_t Certificate::getCreated() {
    ASN1_TIME *date = X509_get_notBefore(this->certificate);
    return ASN1_TIME_to_time(date);
}

time_t Certificate::getExpires() {
    ASN1_TIME *date = X509_get_notAfter(this->certificate);
    return ASN1_TIME_to_time(date);
}

bool Certificate::operator==(const cert::Certificate &c) {
    return this->getThumbprint() == c.getThumbprint();
}

vector<CertificateExtension *> Certificate::getExtensions() {
    const stack_st_X509_EXTENSION *extensions = X509_get0_extensions(this->getX509());
    vector<CertificateExtension *> exts;

    for (int i = 0; i < sk_X509_EXTENSION_num(extensions); i++) {
        exts.push_back(new CertificateExtension(sk_X509_EXTENSION_value(extensions, i)));
    }

    return exts;
}

int Certificate::sign(EVP_PKEY *pKey) {
    int res = X509_sign(this->certificate, pKey, EVP_sha256());
    return res;
}

void Certificate::addBasicConstraints(bool ca, int pathLen) {
    ASN1_INTEGER *pl = ASN1_INTEGER_new();
    ASN1_INTEGER_set_int64(pl, pathLen);

    BASIC_CONSTRAINTS basicConstraints = {
            (int) ca,
            pl
    };

    // TODO: error handling
    X509_add1_ext_i2d(certificate, NID_basic_constraints, &basicConstraints, true, X509V3_ADD_APPEND);
}

void Certificate::appendExtension(X509_EXTENSION *ext) {
    X509_add_ext(certificate, ext, -1);
}
