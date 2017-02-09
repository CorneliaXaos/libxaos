#ifndef     LIBXAOS_CORE_STRINGS_HASHED_STRING_H
#define     LIBXAOS_CORE_STRINGS_HASHED_STRING_H

#include <cstdint>

#include "strings/StringPool.h"

namespace libxaos {
    namespace strings {

        //! The number used in the hashing.
        using HashType = uint32_t;

        class HashedString {

            public:

                //! Construct a HashedString from a character literal
                HashedString(const char*);
                //! Construct a HashedString from a std::string (convenience)
                HashedString(std::string&);
                //! Cosntruct a HashedString from a PooledString
                HashedString(const PooledString&);
                ~HashedString();

                HashedString(const HashedString&);
                HashedString& operator=(const HashedString&);
                HashedString(HashedString&&);
                HashedString& operator=(HashedString&&);

                //! Returns the hash of the string used in construction.
                inline HashType getHash() const;

            private:
                HashType _hash;
        };

    }
}

#endif   // LIBXAOS_CORE_STRINGS_HASHED_STRING_H
