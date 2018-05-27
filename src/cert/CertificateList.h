#include "Certificate.h"

using std::vector;

namespace cert {

    class CertificateList {

    public:
        CertificateList();

        vector<Certificate*>* listAll();

        void add(Certificate*);

        void remove(Certificate*);

        long find(Certificate*);

    private:
        vector<Certificate*>* certificates;
    };

}
