#include <unordered_set>
#include "Certificate.h"

using std::unordered_set;

namespace cert {

    class CertificateList {

    public:
        CertificateList();

        unordered_set<Certificate *> *listAll();

        void add(Certificate *);

        void remove(Certificate *);

        int find(Certificate *);

    private:
        unordered_set<Certificate *> *certificates;
    };

}
