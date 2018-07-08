#ifndef CERTIFICATELIST_H
#define CERTIFICATELIST_H

#include <unordered_set>
#include "Certificate.h"

using std::unordered_set;

namespace cert {

    struct CertificateEqualByThumbprint {
    public:
        bool operator()(const Certificate *lhs, const Certificate *rhs) const;
    };

    struct CertificateHashByThumbprint {
    public:
        size_t operator()(const Certificate *cert) const;
    };

    typedef unordered_set<Certificate *, CertificateHashByThumbprint, CertificateEqualByThumbprint> CertificateListSet;

    class CertificateList {

    public:
        CertificateList();

        CertificateListSet *listAll();

        void add(Certificate *);

        void remove(Certificate *);

    private:
        CertificateListSet *certificates;
    };
}

#endif
