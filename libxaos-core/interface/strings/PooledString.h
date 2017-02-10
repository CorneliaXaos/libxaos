#ifndef     LIBXAOS_CORE_STRINGS_POOLED_STRING_H
#define     LIBXAOS_CORE_STRINGS_POOLED_STRING_H

#include <cstddef>

#include "strings/StringPool.h"

namespace libxaos {
    namespace strings {

        /**
         *  @brief Represents a string in a StringPool.
         *
         *  Represents a pooled string in memory.  Does NOT allow user
         *  construction and is only constructible by StringPool objects. This
         *  is to ensure that no user can instantiate a PooledString from
         *  nowhere.  (Though comparisons are allowed.)
         */
        class PooledString {

            //! The StringPool class needs to be a friend of the PooledString
            friend class StringPool;

            public:
                //! Allow direct construction of a nullptr string.
                PooledString(nullptr_t);
                ~PooledString();

                PooledString(const PooledString&);
                PooledString& operator=(const PooledString&);
                PooledString(PooledString&&);
                PooledString& operator=(PooledString&&);

                //! Allow assigning nullptr to PooledString
                PooledString& operator=(nullptr_t);

                //! Determines if this PooledString points to a valid string.
                operator bool() const;

                //! Acquires the contents of this PooledString
                const char* getCharPointer() const;

                //! Compares two PooledStrings (Equality)
                bool operator==(const PooledString&);
                //! Compares two PooledStrings (Inequality)
                bool operator!=(const PooledString&);

            private:
                //! Private constructor for use by the StringPool
                PooledString(char*);

                //! Raw string pointer referencing to StringPool memory.
                char* _string;
        };

    }
}

#endif   // LIBXAOS_CORE_STRINGS_POOLED_STRING_H
