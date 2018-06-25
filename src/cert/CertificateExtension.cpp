#include <openssl/x509v3.h>
#include "CertificateExtension.h"

using std::pair;

using namespace cert;

CertificateExtension::CertificateExtension(X509_EXTENSION *extension) : extension(extension) {
}

CertificateExtension::~CertificateExtension() {
    X509_EXTENSION_free(extension);
}

bool CertificateExtension::critical() {
    return X509_EXTENSION_get_critical(extension) == 1;
}

int CertificateExtension::typeNID() {
    auto obj = X509_EXTENSION_get_object(extension);
    return OBJ_obj2nid(obj);
}

string cert::CertificateExtension::type() {
    auto obj = X509_EXTENSION_get_object(extension);

    int bufLen = OBJ_obj2txt(NULL, 0, obj, 0) + 1; // +1 because string terminator
    char buffer[bufLen];
    OBJ_obj2txt(buffer, bufLen, obj, 0);

    return string(buffer);
}

void *CertificateExtension::value() {
    return X509V3_EXT_d2i(extension);
}
