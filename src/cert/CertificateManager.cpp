
#include <string>
#include <openssl/pem.h>
#include <QtCore/QDirIterator>
#include "CertificateManager.h"
#include "../core/Environment.h"

using std::string;
using std::vector;
using core::Environment;

using namespace cert;

CertificateManager::CertificateManager() {
    this->certificateList = new vector<Certificate>;
}

void CertificateManager::importCertificate(string path) {
    X509 *x509 = getX509(path);
    if (x509 == nullptr)
        return;

    auto *cert = new Certificate(x509);

    addCertificateToList(cert);

    exportCertificate(cert, Environment::getCertificatesDir(), std::to_string(X509_issuer_and_serial_hash(x509)));
}

void CertificateManager::exportCertificate(Certificate *cert, string path, string filename) {
    X509 *x509 = cert->getX509();
    path.append("/" + filename + ".pem");
    auto bio = BIO_new_file(path.c_str(), "w");
    PEM_write_bio_X509(bio, x509);
    BIO_flush(bio);
}


vector<Certificate> *CertificateManager::getCertificateList() {
    return this->certificateList;
}

void CertificateManager::loadCertificates() {
    const QString &dir = QString::fromStdString(Environment::getCertificatesDir());
    QDirIterator it(dir, QStringList(), QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QFileInfo fi(QFile(it.next()));
        string path = fi.filePath().toStdString();
        X509 *x509 = getX509(path);
        if (x509 == nullptr)
            return;

        auto *cert = new Certificate(x509);

        addCertificateToList(cert);
    }
}

void CertificateManager::addCertificateToList(Certificate *certificate) {
    if (!(find(certificateList->begin(), certificateList->end(), *certificate) != certificateList->end())) {
        //Certificate not found -> add
        certificateList->push_back(*certificate);
    }
}

X509 *CertificateManager::getX509(string path) {
    auto bio = BIO_new_file(path.c_str(), "r");
    X509 *x509 = PEM_read_bio_X509(bio, NULL, NULL, NULL);

    return x509;
}
