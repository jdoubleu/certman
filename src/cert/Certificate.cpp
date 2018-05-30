#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <sstream>
#include "Certificate.h"
#include "util.h"

using std::stringstream;
using std::vector;

using namespace cert;

Certificate::Certificate(X509 *certificate) : certificate(certificate) {
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

string Certificate::getSignatureAlgorithm() {
    return OBJ_nid2ln(X509_get_signature_type(this->certificate));
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

vector<string> Certificate::getASN() {
    vector<string> list;
    auto *subjectAltNames = (GENERAL_NAMES *) X509_get_ext_d2i(
            this->certificate, NID_subject_alt_name, nullptr, nullptr
    );
    for (int i = 0; i < sk_GENERAL_NAME_num(subjectAltNames); i++) {
        GENERAL_NAME *gen = sk_GENERAL_NAME_value(subjectAltNames, i);
        if (gen->type == GEN_URI || gen->type == GEN_DNS || gen->type == GEN_EMAIL) {
            ASN1_IA5STRING *asn1_str = gen->d.uniformResourceIdentifier;
            string san = string((char *) ASN1_STRING_get0_data(asn1_str));
            list.push_back(san);
        } else if (gen->type == GEN_IPADD) {
            unsigned char *p = gen->d.ip->data;
            if (gen->d.ip->length == 4) {
                stringstream ip;
                ip << (int) p[0] << '.' << (int) p[1] << '.' << (int) p[2] << '.' << (int) p[3];
                list.push_back(ip.str());
            }
        }
    }
    GENERAL_NAMES_free(subjectAltNames);
    return list;
}

bool Certificate::operator==(const cert::Certificate &c) {
    return this->getThumbprint() == c.getThumbprint();
}


