#include <algorithm>
#include "CertificateList.h"

using std::vector;

using namespace cert;


CertificateList::CertificateList() {
    this->certificates = new vector<Certificate*>;
}

vector <Certificate*>* CertificateList::listAll() {
    return this->certificates;
}

void CertificateList::add(Certificate * cert) {
    if (this->find(cert) == -1) {
        //Certificate not found -> add
        this->certificates->push_back(cert);
    }
}

void CertificateList::remove(Certificate * cert) {
    auto pos = this->find(cert);
    if(pos >= 0) {
        this->certificates->erase(this->certificates->begin() + pos);
    }
}

long CertificateList::find(Certificate *cert) {
    return std::distance(this->certificates->begin(), std::find(this->certificates->begin(), this->certificates->end(), cert)) -1;
}
