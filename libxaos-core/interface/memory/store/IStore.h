#ifndef   LIBXAOS_MEMORY_STORE_H
#define   LIBXAOS_MEMORY_STORE_H

#include <cstdint>
#include <cstdlib>

namespace libxaos {
    namespace memory {

        /**
         *  @brief The interface for classes that represent data stores.
         *
         *  This class interface represents an accessible data store. This data
         *  store should be valid so long as the class is initialized.  There
         *  are no limitations on whether or not all INSTANCES of a class SHARE
         *  a store or not but, generally, this is not a good idea.
         *
         *  To ensure ease of use, a Store should be default constructable.
         */
        template<size_t N>
        class IStore {
            static_assert(N > 0, "A Store must have non-zero storage size!");

            public:
                virtual ~Store() {}; //!< Virtual No-Action Destructor

                /**
                 *  @brief Returns a "byte" pointer to the beginning of the data
                 *  store.
                 *
                 *  This method returns a pointer to the beginning of the data
                 *  in memory that the using class shall utilize for storing
                 *  information.
                 */
                virtual uint8_t* getRawStorage() = 0;

                //! The size, in bytes, which this store contains.
                static constexpr const size_t SIZE = N;
        };

    }
}

#endif // LIBXAOS_MEMORY_STORE_STORE_H
