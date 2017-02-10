#ifndef     LIBXAOS_CORE_MEMORY_STORE_H
#define     LIBXAOS_CORE_MEMORY_STORE_H

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
        class IStore {

            public:
                //! Initializes the IStore to have particular size and alignment
                IStore(size_t size, unsigned short alignment) :
                        SIZE(size), ALIGNMENT(alignment) {}
                virtual ~IStore() {} //!< Virtual No-Action Destructor

                //! No copying IStores.  They point at UNIQUE memory.
                IStore(const IStore&) = delete;
                IStore& operator=(const IStore&) = delete;

                //! No moving stores.. use a UniquePointer or something..
                IStore(IStore&&) = delete;
                IStore& operator=(IStore&&) = delete;

                /**
                 *  @brief Returns a "byte" pointer to the beginning of the data
                 *  store.
                 *
                 *  This method returns a pointer to the beginning of the data
                 *  in memory that the using class shall utilize for storing
                 *  information.
                 */
                virtual uint8_t* getRawStorage() = 0;

                //! The size_t, in bytes, which this store contains.
                const size_t SIZE;
                //! The short at which the data should be aligned.
                const unsigned short ALIGNMENT;
        };

    }
}

#endif //   LIBXAOS_CORE_MEMORY_STORE_STORE_H
