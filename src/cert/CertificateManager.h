#ifndef CERTIFICATEMANAGER_H
#define CERTIFICATEMANAGER_H

#include <QtCore>
#include "Certificate.h"
#include "CertificateList.h"

using std::vector;

namespace cert {

    /**
     * Callback function which is used to process the key pair before exporting.
     * E.g. key wrapping with algorithm and password.
     * @param sink BIO to write to
     */
    typedef std::function<void(BIO *sink)> EXPORT_PRIVATEKEY_FUNC;

    /**
     * Container structure used whenever a key pair is exported or internally passed
     */
    typedef struct {

        /**
         * Reference to the OpenSSL key pair structure.
         */
        EVP_PKEY *keyPair;

        /**
         * Function used for exporting of the above key pair.
         */
        EXPORT_PRIVATEKEY_FUNC exportFunc;
    } KEYPAIR_EXPORT;

    /**
     * Container structure used for exporting whole certificates.
     */
    typedef struct {

        /**
         * The subject of this export.
         */
        Certificate *certificate;

        /**
         * Belonging key pair export container structure of the above certificate.
         */
        KEYPAIR_EXPORT keyPairExport;
    } CERT_EXPORT;

    /**
     * Class represents a manager to handle logic for certificates.
     */
    class CertificateManager {
    Q_DECLARE_TR_FUNCTIONS(CertificateManager)

    public:

        /**
         * Constructor for a certificateManager.
         */
        CertificateManager();

        /**
         * Removes a certificate from the application.
         * @param cert Certificate to remove.
         * @return Boolean if successful or not
         */
        bool removeCertificate(Certificate *cert);

        /**
         * Import a certificate into the application.
         * @param pathCert Path of the certificate to be imported.
         * @param pathPrivateKey Path of the key of the certificate to be imported.
         */
        void importCertificate(string pathCert, string pathPrivateKey);

        /**
         * Export a certificate to a location.
         * @param cert Certificate to export.
         * @param path Location to export to.
         */
        void exportCertificate(Certificate *cert, string path);

        /**
         * Export a private key to a location.
         * @param origin Original location of the private key.
         * @param destination Target location of the private key.
         */
        void exportPrivateKeyFile(string origin, string destination);

        /**
         * Export a private key to a location.
         * @param pkey Private key to export.
         * @param location Location to export to.
         */
        void exportPrivateKey(EVP_PKEY *pkey, string location);

        /**
         * Get all current certificates.
         * @return CertificateList containing all current certificates.
         */
        CertificateList *getCertificateList();

        /**
         * Loads all certificates from the certman directory into the application.
         */
        void loadCertificates();

        /**
         * Loads an X509 object from a path.
         * @param path Path to load the X509 from.
         * @return Loaded X509 object.
         */
        X509 *getX509(string path);

        /**
         * Loads a private key from a path.
         * @param path Path to load the private key from.
         * @return Loaded EVP_KEY.
         */
        EVP_PKEY *getKey(string path);

        /**
         * Checks if a certificate has a private key.
         * @param cert Certificate to check.
         * @return Boolean if certificate has a private key.
         */
        bool hasPrivateKey(Certificate *cert);

        /**
         * Get the default location of a given certificate.
         * @param cert Certificate to get location from.
         * @return Location of the certificate.
         */
        string getCertificateDefaultLocation(Certificate *cert);

        /**
         * Get the default location of a key from a certificate.
         * @param cert Certificate to get key location from.
         * @return Location of the key.
         */
        string getPrivateKeyDefaultLocation(Certificate *cert);

        /**
         * Creates a new certificate.
         * @param subject Subject of the certificate.
         * @param issuer Issuer of the certificate.
         * @param validityDays Validity in days of the certificate.
         * @param keyPair KeyPair of the certificate.
         * @param signMd Signature message digest of the certificate.
         * @param serialNumber SerialNumber of the certificate.
         * @return The created certificate.
         */
        Certificate *createCertificate(X509_NAME *subject, X509_NAME *issuer, int validityDays, EVP_PKEY *keyPair,
                                       const EVP_MD *signMd, long serialNumber = 1);

        /**
         * Creates a new certificate.
         * @param subject Subject of the certificate.
         * @param issuer Issuer of the certificate.
         * @param validityDays Validity in days of the certificate.
         * @param keyPair KeyPair of the certificate.
         * @param serialNumber SerialNumber of the certificate.
         * @return The created certificate.
         */
        Certificate *createCertificate(X509_NAME *subject, X509_NAME *issuer, int validityDays, EVP_PKEY *keyPair,
                                       long serialNumber = 1);

        /**
         * Gets all certificates inside a X509_STORE object.
         * @return X509_STORE object containing all certificats.
         */
        X509_STORE *getCertificateListAsX509Store();

        /**
         * Signs a given certificate.
         * @param cert Certificate to sign.
         * @param signer The certificate used to sign cert.
         * @return Boolean if signing was successful.
         */
        bool signCertificate(Certificate *cert, Certificate *signer);

        /**
         * Genertes a key pair.
         * @param algorithm Algorithm used.
         * @param keySize Keysize used.
         * @return Created private key.
         */
        EVP_PKEY *generateKeyPair(int algorithm, int keySize);

        /**
         * Generates keyUsageExtensions.
         * @param critical Is critical.
         * @param digitalSignature Allow digitalSignature.
         * @param nonRepudiation Allow nonRepudiation.
         * @param keyEncipherment Allow keyEncipherment.
         * @param dataEncipherment Allow dataencipherment,
         * @param keyAgreement Allow keyAgreement.
         * @param keyCertSign Allow keyCertSigning.
         * @param cRLSign Allow CRLSigning.
         * @param encipherOnly Allow encipherOnly.
         * @param decipherOnly Allow decipherOnly.
         * @return X509_EXTENSION containing all extensions.
         */
        X509_EXTENSION *
        generateKeyUsageExtensions(bool critical, bool digitalSignature = false, bool nonRepudiation = false,
                                   bool keyEncipherment = false,
                                   bool dataEncipherment = false, bool keyAgreement = false, bool keyCertSign = false,
                                   bool cRLSign = false, bool encipherOnly = false,
                                   bool decipherOnly = false);

        /**
         * Imports a new certificate into the application.
         * @param newCertificate Certificate to import.
         */
        void importNewCertificate(CERT_EXPORT newCertificate);

    private:

        /**
         * CertificateList of all certificates.
         */
        CertificateList *certificateList;
    };

}

#endif
