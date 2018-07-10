#ifndef CERTIFICATE_H
#define CERTIFICATE_H

#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <string>
#include <openssl/ossl_typ.h>
#include <vector>
#include <map>
#include <QtGui>
#include "CertificateExtension.h"

using std::string;
using std::vector;
using std::map;
using cert::CertificateExtension;

namespace cert {

    /**
     * Represents a X509 certificate.
     */
    class Certificate {
    public:

        /**
         * Constructor for a certificate.
         * @param certificate X509 Object of the certificate.
         */
        explicit Certificate(X509 *certificate);

        /**
         * Get the X509 object of the certificate.
         * @return The X509 object of the certificate.
         */
        X509 *getX509();

        /**
         * Get the version of the certificate.
         * @return The current version.
         */
        long getVersion();

        /**
         * Get the thumbprint of the certificate.
         * @return The current thumbprint.
         */
        string getThumbprint() const;

        /**
         * Get the issuer of the certificate.
         * @return The current issuer.
         */
        string getIssuer();

        /**
         * Get the issuerFields of the certificate.
         * @return Map containing the issuerFields.
         */
        map<string, string> getIssuerFields();

        /**
         * Get an issuerField of the certificate.
         * @param field Identifier of the issuerField to get.
         * @return The issuerField of the certificate.
         */
        string getIssuerField(const string field);

        /**
         * Get the subject of the certificate.
         * @return The subject of the certificate.
         */
        string getSubject();

        /**
         * Get the subjectFields of the certificate.
         * @return Map containing the subjectFields.
         */
        map<string, string> getSubjectFields();

        /**
         * Get an subjectField of the certificate.
         * @param field Identifier if the subjectField to get.
         * @return The SubjectField of the certificate.
         */
        string getSubjectField(const string field);

        /**
         * Get the keyType of the certificates key.
         * @return KeyType of the certificates key.
         */
        string getKeyType();

        /**
         * Get the keySize of the certificates key.
         * @return KeySize of the certificates key.
         */
        int getKeySize();

        /**
         * Get the time the certificates is valid from.
         * @return time_t object with timestamp the certificate is valid from.
         */
        time_t getCreated();

        /**
         * Get the time the certificate is valid to.
         * @return time_t object with timestamp the certificate is valid to.
         */
        time_t getExpires();

        /**
         * Get the extensions of the certificate.
         * @return The extensions of the certificate.
         */
        vector<CertificateExtension *> getExtensions();

        /**
         * Signs the certificate.
         * @param pKey PrivateKey to use for signing process.
         * @return Size of signature in bytes or zero for failure.
         */
        int sign(EVP_PKEY *pKey);

        /**
         * Adds a basic constraint.
         * @param ca Boolean if certificate is a CA.
         * @param pathLen PathLength of the certificate.
         */
        void addBasicConstraints(bool ca, int pathLen);

        /**
         * Appends an extension to the certificate.
         * @param ext Extension to append.
         */
        void appendExtension(X509_EXTENSION *ext);

        /**
         * Operator to compare two certificates,
         * @param c Certificate to compare with.
         * @return Boolen if they are equal or not.
         */
        bool operator==(const Certificate &c);

    private:

        /**
         * The X509 object of the certificate.
         */
        X509 *certificate;

    };
}

Q_DECLARE_METATYPE(cert::Certificate*);

#endif
