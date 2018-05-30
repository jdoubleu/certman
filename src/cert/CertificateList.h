#ifndef CERTIFICATELIST_H
#define CERTIFICATELIST_H

#include <unordered_set>
#include "Certificate.h"

using std::unordered_set;

namespace cert {

    class CertificateList {

    public:
        CertificateList();

        struct CertificateEqualByThumbprint {
        public:
            bool operator()(const Certificate *lhs, const Certificate *rhs) const;
        };

        struct CertificateHashByThumbprint {
        public:
            size_t operator()(const Certificate *cert) const;
        };

        unordered_set<Certificate *, CertificateList::CertificateHashByThumbprint, CertificateList::CertificateEqualByThumbprint> *
        listAll();

        void add(Certificate *);

        void remove(Certificate *);

    private:
        unordered_set<Certificate *, CertificateHashByThumbprint, CertificateEqualByThumbprint> *certificates;
    };

}

#endif
