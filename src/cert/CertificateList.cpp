#include "CertificateList.h"

using std::hash;

using namespace cert;

bool CertificateEqualByThumbprint::operator()(const Certificate *lhs, const Certificate *rhs) const {
    return lhs->getThumbprint() == rhs->getThumbprint();
}

size_t CertificateHashByThumbprint::operator()(const Certificate *cert) const {
    return std::hash<string>()(cert->getThumbprint());
}

CertificateList::CertificateList() {
    certificates = new unordered_set<Certificate *, CertificateHashByThumbprint, CertificateEqualByThumbprint>;
}

CertificateListSet *CertificateList::listAll() {
    return certificates;
}

void CertificateList::add(Certificate *cert) {
    certificates->insert(cert);
}

void CertificateList::remove(Certificate *cert) {
    certificates->erase(cert);
}
