#ifndef CERTIFICATEEXTENSION_H
#define CERTIFICATEEXTENSION_H

#include <openssl/x509.h>
#include <string>
#include <map>

using std::string;
using std::map;

namespace cert {

    /**
     * Represents a X509_EXTENSION.
     */
    class CertificateExtension {
    public:
        /**
         * Constructor for a extension.
         * @param extension X509_EXTENSION Reference to the X509_EXTENSION.
         */
        explicit CertificateExtension(X509_EXTENSION *extension);

        /**
         * Destructor for the extension.
         */
        ~CertificateExtension();

        /**
         * Checks if the extension is critical.
         * @return Get critical status.
         */
        bool critical();

        /**
         * Get type in NID format.
         * @return NID.
         */
        int typeNID();

        /**
         * Get type of the extension.
         * @return Type.
         */
        string type();

        /**
         * Prints the extension.
         * @return Extension formatted as a String.
         */
        string sprint();

    private:
        /**
         * Reference to the X509_EXTENSION structure.
         */
        X509_EXTENSION *extension;

        /**
         * Get the extension structure.
         * @return Reference to a internal structure.
         */
        void *value();
    };

}

#endif
