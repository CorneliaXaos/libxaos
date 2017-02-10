#ifndef     LIBXAOS_CORE_STRINGS_POOLED_STRING_H
#define     LIBXAOS_CORE_STRINGS_POOLED_STRING_H

#include <cstddef>

namespace libxaos {
    namespace strings {

        // Forward declare StringPool
        class StringPool;

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
                inline operator bool() const;

                //! Acquires the contents of this PooledString
                inline const char* getCharPointer() const;

            private:
                //! Private constructor for use by the StringPool
                explicit PooledString(char*);

                //! Raw string pointer referencing to StringPool memory.
                char* _string;
        };

        //! Compares two PooledStrings (Equality)
        inline bool operator==(const PooledString&, const PooledString&) const;
        //! Compares two PooledStrings (Inequality)
        inline bool operator!=(const PooledString&, const PooledString&) const;
        //! Compares to nullptr (Equality)
        inline bool operator==(const PooledString&, nullptr_t) const;
        //! Compares to nullptr (Equality)
        inline bool operator==(nullptr_t, const PooledString&) const;
        //! Compares to nullptr (Inequality)
        inline bool operator!=(const PooledString&, nullptr_t) const;
        //! Compares to nullptr (Inequality)
        inline bool operator!=(nullptr_t, const PooledString&) const;

    }
}

// Bring in inline implementations
#include "PooledString-inl.h"

#endif   // LIBXAOS_CORE_STRINGS_POOLED_STRING_H
