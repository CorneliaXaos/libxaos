#ifndef     LIBXAOS_CORE_STRINGS_HASHED_STRING_H
#define     LIBXAOS_CORE_STRINGS_HASHED_STRING_H

#include <cstdint>
#include <string>

namespace libxaos {
    namespace strings {

        // Forward declare PooledString
        class PooledString;

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
                explicit HashedString(const std::string&);
                //! Cosntruct a HashedString from a PooledString
                explicit HashedString(const PooledString&);
                ~HashedString();

                HashedString(const HashedString&);
                HashedString& operator=(const HashedString&);
                HashedString(HashedString&&);
                HashedString& operator=(HashedString&&);

                //! Returns the hash of the string used in construction.
                inline HashType getHash() const { return _hash; }

                //! Unique hash for nullptr strings
                static const HashType NULL_STRING_HASH;
                //! Unique hash for empty strings
                static const HashType EMPTY_STRING_HASH;

                //! Uniquely identifies all nullptr strings
                static const HashedString NULL_STRING;
                //! Uniquely identifies all empty strings
                static const HashedString EMPTY_STRING;

            private:
                //! This string's HashType / Value
                HashType _hash;
        };

        //! Equality operator of two HashedStrings
        inline bool operator==(const HashedString&, const HashedString&);
        //! Inequality operator of two HashedStrings
        inline bool operator!=(const HashedString&, const HashedString&);
        //! Equality operator of HashedString and HashType
        inline bool operator==(const HashedString&, HashType);
        //! Equality operator of HashType and HashedString
        inline bool operator==(HashType, const HashedString&);
        //! Inequality operator of HashedString and HashType
        inline bool operator!=(const HashedString&, HashType);
        //! Inequality operator of HashType and HashedString
        inline bool operator!=(HashType, const HashedString&);
    }
}

// Bring in inline implementations
#include "HashedString-inl.h"

#endif   // LIBXAOS_CORE_STRINGS_HASHED_STRING_H
