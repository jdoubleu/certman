#include <vector>
#include "Certificate.h"

using namespace std;

namespace {

class CertificateList {
protected:
    vector<Certificate> certificates;

public:
    void load();
    vector<Certificate> listAll();
    void add(Certificate);
};

}
