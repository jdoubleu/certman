#include <vector>
#include "Certificate.h"

using std::vector;

namespace cert {

class CertificateList {
protected:
    vector<Certificate> certificates;

public:
    void load();
    vector<Certificate> listAll();
    void add(Certificate);
};

}
