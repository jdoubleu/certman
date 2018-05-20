#include "Certificate.h"

class CertificateManager {
public:
    Certificate createCertificate();
    void signCertificate();
    void importCertificate();
    void exportCertificate();

protected:
    void createKeyPair();
};


