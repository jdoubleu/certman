#include "CertificateList.h"

using namespace cert;


CertificateList::CertificateList() {
    certificates = new unordered_set<Certificate *>;
}

unordered_set<Certificate *> *CertificateList::listAll() {
    return certificates;
}

void CertificateList::add(Certificate *cert) {
    certificates->insert(cert);
}

void CertificateList::remove(Certificate *cert) {
    certificates->erase(cert);
}

