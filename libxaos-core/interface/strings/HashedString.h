#ifndef     LIBXAOS_CORE_STRINGS_HASHED_STRING_H
#define     LIBXAOS_CORE_STRINGS_HASHED_STRING_H

#include <cstdint>
#include <string>

#include "strings/PooledString.h"

namespace libxaos {
    namespace strings {

        //! The number used in the hashing.
        using HashType = uint32_t;

        /**
         *  @brief Represents a mechaism for converting strings into hashes.
         *
         *  This class represents an interface to convert strings to hashes
         *  while simultaneously holding said hash.  It should be noted that
         *  there are two special cases that may affect the spread of this
         *  hash (only minutely).  The very real possibility of a user
         *  attempting to hash a nullptr or an empty string exists.  As such,
         *  the hash manually assigns values of HashType to both nullptr and
         *  the empty string.  In the event that a non-empty string resolves
         *  to one of these hardcoded values, it is shifted slightly away from
         *  the value to a valid hash code.
         */
        class HashedString {

            public:

                //! Construct a HashedString from a character literal
                explicit HashedString(const char*);
                //! Construct a HashedString from a std::string (convenience)
                explicit HashedString(std::string&);
                //! Cosntruct a HashedString from a PooledString
                explicit HashedString(const PooledString&);
                ~HashedString();

                HashedString(const HashedString&);
                HashedString& operator=(const HashedString&);
                HashedString(HashedString&&);
                HashedString& operator=(HashedString&&);

                //! Returns the hash of the string used in construction.
                inline HashType getHash() const;

                //! Uniquely identifies all nullptr strings
                static HashType NULL_STRING;
                //! Uniquely identifies all empty strings
                static HashType EMPTY_STRING;

            private:
                HashType _hash;
        };

        //! Equality operator of two HashedStrings
        inline bool operator==(const HashedString&, const HashedString&);
        //! Inequality operator of two HashedStrings
        inline bool operator!=(const HashedString&, const HashedString&);
    }
}

#endif   // LIBXAOS_CORE_STRINGS_HASHED_STRING_H
