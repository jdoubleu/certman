#include <string>
#include <openssl/pem.h>
#include <QtCore/QDirIterator>
#include "CertificateManager.h"
#include "../gui/dialog/PasswordDialog.h"
#include "../core/Environment.h"

using std::string;
using std::vector;
using core::Environment;

using namespace cert;

CertificateManager::CertificateManager() {
    this->certificateList = new CertificateList();
}

void CertificateManager::importCertificate(string pathCert, string pathPrivateKey) {
    X509 *x509 = getX509(pathCert);
    if (x509 == nullptr)
        return;

    auto *cert = new Certificate(x509);

    if (!pathPrivateKey.empty()) {
        EVP_PKEY *key = getKey(pathPrivateKey);
        auto valid = X509_verify(x509, key);

        if (valid != 1)
            return;

        exportPrivateKeyFile(pathPrivateKey, getPrivateKeyDefaultLocation(cert));
    }

    this->certificateList->add(cert);

    exportCertificate(
            cert,
            getCertificateDefaultLocation(cert)
    );


}

void CertificateManager::exportCertificate(Certificate *cert, string path) {
    X509 *x509 = cert->getX509();
    auto bio = BIO_new_file(path.c_str(), "w");
    PEM_write_bio_X509(bio, x509);
    BIO_flush(bio);
    BIO_free(bio);
}


CertificateList *CertificateManager::getCertificateList() {
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
            continue;

        auto *cert = new Certificate(x509);

        this->certificateList->add(cert);
    }
}


X509 *CertificateManager::getX509(string path) {
    auto bio = BIO_new_file(path.c_str(), "r");
    X509 *x509 = PEM_read_bio_X509(bio, NULL, NULL, NULL);

    if (x509 == NULL) {
        BIO_reset(bio);
        x509 = d2i_X509_bio(bio, NULL);
    }

    BIO_free(bio);

    return x509;
}

EVP_PKEY *CertificateManager::getKey(string path) {
    auto bio = BIO_new_file(path.c_str(), "r");
    EVP_PKEY *pkey = PEM_read_bio_PrivateKey(bio, NULL, gui::dialog::passwordCallback, NULL);
    BIO_free(bio);
    return pkey;
}

string CertificateManager::getCertificateDefaultLocation(Certificate *cert) {
    return Environment::getCertificatesDir() + "/" + cert->getThumbprint() + ".pem";
}

string CertificateManager::getPrivateKeyDefaultLocation(Certificate *cert) {
    return Environment::getCertificatesDir() + "/" + cert->getThumbprint() + "_key.pem";
}

void CertificateManager::exportPrivateKeyFile(string origin, string destination) {
    QFile::copy(QString::fromStdString(origin), QString::fromStdString(destination));
}

bool CertificateManager::hasPrivateKey(Certificate *cert) {
    return QFile::exists(QString::fromStdString(getPrivateKeyDefaultLocation(cert)));
}

void CertificateManager::exportPrivateKey(EVP_PKEY *pkey, string location) {
    auto bio = BIO_new_file(location.c_str(), "w");
    auto label = tr("Please enter passphrase.").toStdString();
    PEM_write_bio_PrivateKey(bio, pkey, EVP_des_ede3_cbc(), NULL, 0, gui::dialog::passwordCallback, &label);
    BIO_flush(bio);
    BIO_free(bio);
}

bool CertificateManager::removeCertifcate(Certificate *cert) {
    bool success = QFile::remove(QString::fromStdString(getCertificateDefaultLocation(cert)));

    if (!success)
        return false;

    if (hasPrivateKey(cert))
        QFile::remove(QString::fromStdString(getPrivateKeyDefaultLocation(cert)));

    this->certificateList->remove(cert);

    return true;
}

Certificate* CertificateManager::createCertificate(X509_NAME *subject, X509_NAME *issuer, int validityDays,
                                                  EVP_PKEY *keyPair,
                                                  const EVP_MD *signMd, long serialNumber) {
    // TODO: error handling

    X509 *x509 = X509_new();

    // Version (X509 v3)
    X509_set_version(x509, 2);

    // Serial Number
    ASN1_INTEGER_set(X509_get_serialNumber(x509), serialNumber);

    // Validity
    ASN1_TIME *tmFrom = ASN1_TIME_adj(NULL, time(NULL), 0, 0);
    X509_set1_notBefore(x509, tmFrom);
    ASN1_TIME *tmAfter = ASN1_TIME_adj(NULL, time(NULL), validityDays, 0);
    X509_set1_notAfter(x509, tmAfter);

    // Subject and Issuer
    X509_set_subject_name(x509, subject);
    X509_set_issuer_name(x509, issuer);

    // Keys and Signing
    X509_set_pubkey(x509, keyPair);
    X509_sign(x509, keyPair, signMd);

    // Validation
    if (X509_verify(x509, keyPair) != 1) {
        return NULL;
    }

    return new Certificate(x509);
}

Certificate *
CertificateManager::createCertificate(X509_NAME *subject, X509_NAME *issuer, int validityDays, EVP_PKEY *keyPair,
                                      long serialNumber) {
    return createCertificate(subject, issuer, validityDays, keyPair, EVP_sha256(), serialNumber);
}

EVP_PKEY *CertificateManager::generateKeyPair(int algorithm, int keySize) {
    // TODO: error handling
    EVP_PKEY *keyPair = EVP_PKEY_new();
    EVP_PKEY_CTX *keygenContext = EVP_PKEY_CTX_new_id(algorithm, NULL);

    // Algorithm specific key generation
    switch (algorithm) {
        case EVP_PKEY_RSA:
            EVP_PKEY_CTX_set_rsa_keygen_bits(keygenContext, keySize);
            EVP_PKEY_keygen(keygenContext, &keyPair);
            break;
        case EVP_PKEY_DSA:
            EVP_PKEY_CTX_set_dsa_paramgen_bits(keygenContext, keySize);
            EVP_PKEY_paramgen(keygenContext, &keyPair);
        default:
            break;
    }

    EVP_PKEY_CTX_free(keygenContext);

    return keyPair;
}

X509_STORE *CertificateManager::getCertificateListAsX509Store() {
    X509_STORE *store = X509_STORE_new();
    auto certs = getCertificateList()->listAll();

    for (const auto& cert: *certs) {
        X509_STORE_add_cert(store, cert->getX509());
    }

    X509_STORE_lock(store);

    return store;
}
