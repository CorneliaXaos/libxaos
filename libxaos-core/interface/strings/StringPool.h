#ifndef     LIBXAOS_CORE_STRINGS_STRING_POOL_H
#define     LIBXAOS_CORE_STRINGS_STRING_POOL_H

#include "memory/store/IStore.h"

namespace libxaos {
    namespace strings {

        // Forward declare PooledString
        class PooledString;

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
         *  some point.  In other words, one should not rely on there existing
         *  a StringPool for use until one can confirm that some system provides
         *  such a pool.
         *
         *  It should also be noted that in order to have a decent memory
         *  footprint that NO STRING SHOULD BE LARGER THAN A SHORT'S LENGTH!!!
         *  I REPEAT, MAX LENGTH OF STRING (EXCLUDING NULL CHARACTER) IS
         *  A SHORT (uint16_t).  65536!!!!!
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

                //! Add / Get a String to the Pool
                PooledString process(const char*);
                //! Query if a String is present (const char*)
                bool contains(const char*) const;
                //! Query if a String is present (PooledString)
                bool contains(const PooledString&) const;

            private:
                //! Where we will store our strings
                IStore _store;
                //! The number of strings in the pool.  Needed for adding.
                unsigned int _count;
        };

    }
}

#endif   // LIBXAOS_CORE_STRINGS_STRING_POOL_H
