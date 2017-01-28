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
         *
         *  @tparam N the size_t of bytes this Store contains.
         *  @tparam A the short at which the data should be internally aligned.
         */
        template<size_t N, short A>
        class IStore {
            static_assert(N > 0, "A Store must have non-zero storage size!");

            public:
                virtual ~IStore() {} //!< Virtual No-Action Destructor

                /**
                 *  @brief Returns a "byte" pointer to the beginning of the data
                 *  store.
                 *
                 *  This method returns a pointer to the beginning of the data
                 *  in memory that the using class shall utilize for storing
                 *  information.
                 */
                virtual inline uint8_t* getRawStorage() = 0;

                //! The size_t, in bytes, which this store contains.
                static constexpr const size_t SIZE = N;
                //! The short at which the data should be aligned.
                static constexpr const short ALIGNMENT = A;
        };

    }
}

#endif //   LIBXAOS_CORE_MEMORY_STORE_STORE_H
