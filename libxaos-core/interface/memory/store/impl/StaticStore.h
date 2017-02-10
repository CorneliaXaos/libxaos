#ifndef     LIBXAOS_CORE_MEMORY_STATIC_STORE_H
#define     LIBXAOS_CORE_MEMORY_STATIC_STORE_H

#include <cstdint>
#include <cstdlib>
#include "memory/store/IStore.h"

namespace libxaos {
    namespace memory {

        /**
         *  @brief A StaticStore allocates its data statically.
         *
         *  A StaticStore allocates its data in the static section of the
         *  executable.  This static allocation avoids the troubles of
         *  dynamically acquiring memory for the store at the expense of being
         *  fixed at runtime.
         *
         *  In order to allow multiple static allocations, a Store is a
         *  templated class that takes in an additional identification parameter
         *  which forces the compiler to create an entirely new class for each
         *  ID.  This allows each class to have its own static array of data.
         *
         *  @tparam N the size_t of bytes this store contains.
         *  @tparam A the short at which the data should be internally aligned.
         *  @tparam ID the integer uniquely identifying this static allocation.
         */
        template<size_t N, short A, int ID> //! @todo reserve negative IDs
        class StaticStore : public IStore {

            public:
                StaticStore();
                ~StaticStore();

                //! @todo Copy and Move for the stores? Am not sure...

                //! @see "memory/store/IStore.h"
                inline uint8_t* getRawStorage() override final;

                //! The StaticStore's unique ID.
                static constexpr const int STORE_ID = ID;

            private:
                static uint8_t _store[N]; //!< The Store's static memory.
        };

    }
}

// Bring in template definitions.
#include "StaticStore-tpp.h"

#endif //   LIBXAOS_CORE_MEMORY_STATIC_STORE_H
