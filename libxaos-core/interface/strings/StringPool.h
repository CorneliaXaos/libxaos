#ifndef     LIBXAOS_CORE_STRINGS_STRING_POOL_H
#define     LIBXAOS_CORE_STRINGS_STRING_POOL_H

#include "memory/store/IStore.h"
#include "pointers/IndirectArrayPointer.h"

namespace libxaos {
    namespace strings {

        //! A simple wrapper for the internal string in a StringPool
        using PooledString =
                libxaos::pointers::IndirectArrayPointer<const char*>;

        /**
         *  @brief This class represents a pool of strings.
         *
         *  This class is a "String Pool" in that it holds c-style strings
         *  efficiently.  It allows common strings used by a program to be
         *  cached in a single place and referred to by multiple points in the
         *  program (reducing the need to new char[] for each duplicate string).
         *
         *  This class is NOT provided globally by default, though it is
         *  possible that there may be a global StringPool in the engine at
         *  some point.  In other words, one should not rely on their existing
         *  a StringPool for use until one can confirm that some system provides
         *  such a pool.
         */
        class StringPool {

            public:
                //! An IStore is required to store strings in memory.
                StringPool(IStore&&);
                ~StringPool();

                //! No copying!
                StringPool(const StringPool&) = delete;
                StringPool& operator=(const StringPool&) = delete;

                //! Allow relocating the StringPool
                StringPool(StringPool&&);
                StringPool& operator=(StringPool&&);

                //! Add a String to the Pool
                PooledString add(const char*);
                //! Query if a String is present (const char*)
                inline bool contains(const char*) const;
                //! Query if a String is present (PooledString)
                inline bool contains(const PooledString&) const;

            private:
                //! Where we will store our strings
                IStore _store;
        };

    }
}

#endif   // LIBXAOS_CORE_STRINGS_STRING_POOL_H
