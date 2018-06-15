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
    string label = "Please enter passphrase.";
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

bool CertificateManager::createCertificate(int algorithm, int keySize, int validityDays, X509_NAME *subjectName,
                                           X509_NAME *issuerName) {
    EVP_PKEY *privateKey;
    privateKey = createKeyPair(algorithm, keySize);

    if(privateKey == nullptr)
        return false;

    X509 *x509 = X509_new();

    //Set serialnumber to 1
    ASN1_INTEGER_set(X509_get_serialNumber(x509), 1);

    //Set valid from
    ASN1_TIME *tmFrom = ASN1_TIME_adj(NULL, time(NULL), 0, 0);
    X509_set1_notBefore(x509, tmFrom);

    //Set valid to
    ASN1_TIME *tmAfter = ASN1_TIME_adj(NULL, time(NULL), validityDays, 0);
    X509_set1_notAfter(x509, tmAfter);

    //Set public key
    X509_set_pubkey(x509, privateKey);


    X509_set_subject_name(x509, subjectName);
    X509_set_issuer_name(x509, issuerName);

    //sign certificate
    X509_sign(x509, privateKey, EVP_sha1());

    if(X509_verify(x509,privateKey) != 1)
        return false;

    //Save/export certificate and key
    auto *cert = new Certificate(x509);

    exportPrivateKey(privateKey, getPrivateKeyDefaultLocation(cert));

    exportCertificate(cert, getCertificateDefaultLocation(cert));

    certificateList->add(cert);

    return true;
}

EVP_PKEY *CertificateManager::createKeyPair(int algorithm, int keySize) {
    EVP_PKEY *privateKey;
    privateKey = EVP_PKEY_new();
    EVP_PKEY_CTX *ctx;
    EC_KEY *ecKey;
    int ret = 0;
    switch (algorithm) {
        case EVP_PKEY_RSA:
            ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);
            if (!ctx)
                /* Error occurred */
                ret = -1;

            if (EVP_PKEY_keygen_init(ctx) <= 0)
                /* Error */
                ret = -1;

            if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, keySize) <= 0)
                /* Error */
                ret = -1;

            /* Generate key */
            if (EVP_PKEY_keygen(ctx, &privateKey) <= 0)
                ret = -1;

            if (ret == -1) {
                EVP_PKEY_CTX_free(ctx);
                EVP_PKEY_free(privateKey);
                return nullptr;
            }
            break;
        case EVP_PKEY_EC:
            ecKey = EC_KEY_new_by_curve_name(NID_secp224r1);

            if (!ecKey)
                /* Error occurred */
                ret = -1;

            if (EC_KEY_generate_key(ecKey) != 1)
                ret = -1;

            if (EVP_PKEY_set1_EC_KEY(privateKey, ecKey) <= 0)
                ret = -1;

            if (ret == -1) {
                EC_KEY_free(ecKey);
                EVP_PKEY_free(privateKey);
                return nullptr;
            }
            break;
        case EVP_PKEY_DSA:
            ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_DSA, NULL);
            if (!ctx)
                /* Error occurred */
                ret = -1;

            if (!EVP_PKEY_paramgen_init(ctx))
                ret = -1;

            if (!EVP_PKEY_CTX_set_dsa_paramgen_bits(ctx, keySize))
                ret = -1;

            if (!EVP_PKEY_paramgen(ctx, &privateKey))
                ret = -1;

            if (ret == -1) {
                EVP_PKEY_CTX_free(ctx);
                EVP_PKEY_free(privateKey);
                return nullptr;
            }
            break;
        default:
            break;
    }

    return privateKey;
}
