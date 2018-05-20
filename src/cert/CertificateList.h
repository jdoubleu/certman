#include <vector>
#include "Certificate.h"

using namespace std;

class CertificateList {
protected:
    vector<Certificate> certificates;

public:
    void load();
    vector<Certificate> listAll();
    void add(Certificate);
};
