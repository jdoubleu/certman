
#include <string>
#include <openssl/pem.h>
#include "CertificateManager.h"
#include "../core/Environment.h"

using std::string;
using core::Environment;

using namespace cert;

void CertificateManager::importCertificate(string path) {
    auto bio = BIO_new_file(path.c_str(), "r");
    X509 *x509 = PEM_read_bio_X509(bio, NULL, NULL, NULL);

    if(x509 == NULL) {
       ImportException e;
       e.message="Validation failed";
       throw e;
    }

    exportCertificate(x509, Environment::getCertificatesDir(), std::to_string(X509_issuer_and_serial_hash(x509)));
}

void CertificateManager::exportCertificate(X509 *x509, string path, string filename) {
    path.append("/" + filename + ".pem");
    auto bio = BIO_new_file(path.c_str(), "w");
    PEM_write_bio_X509(bio,x509);
    BIO_flush(bio);
}
