#ifndef CERTIFICATELIST_H
#define CERTIFICATELIST_H

#include <unordered_set>
#include "Certificate.h"

using std::unordered_set;

namespace cert {

    /**
     * Structure to compare certificates by the thumbprint.
     */
    struct CertificateEqualByThumbprint {
    public:

        /**
         * Compares two certificates by there thumbprint.
         * @param lhs First certificate to compare.
         * @param rhs Second certificate to compare.
         * @return Boolean if the certificates are equal.
         */
        bool operator()(const Certificate *lhs, const Certificate *rhs) const;
    };

    /**
     * Structure to create a hash by the thumbprint.
     */
    struct CertificateHashByThumbprint {
    public:

        /**
         * Compares two certificates by their hashes.
         * @param cert Certificate to compare with.
         * @return Boolean if the certificates are equal.
         */
        size_t operator()(const Certificate *cert) const;
    };

    /**
     * A set used for storing certificates internally.
     */
    typedef unordered_set<Certificate *, CertificateHashByThumbprint, CertificateEqualByThumbprint> CertificateListSet;

    /**
     * Class represents a list of certificate objects.
     */
    class CertificateList {
    public:

        /**
         * Constructor for a certificateList.
         */
        CertificateList();

        /**
         * List all certificates.
         * @return unordered set containing all certificates.
         */
        CertificateListSet *listAll();

        /**
         * Adds a certificate to the certificateList.
         * @param cert Certificate to add.
         */
        void add(Certificate *cert);

        /**
         * Removes a certificate from the certificateList.
         * @param cert Certificate to remove.
         */
        void remove(Certificate *cert);

    private:

        /**
         * unordered set of all certificates inside the certificateList.
         */
        CertificateListSet *certificates;
    };
}

#endif
