/**
 *  @file StaticStore-tpp.h
 *  @brief Template Implementations for StaticStore.h
 */

namespace libxaos {
    namespace memory {

        template<size_t N, short A, int ID>
        StaticStore<N, A, ID>::StaticStore() : IStore(N, A) {}

        template<size_t N, short A, int ID>
        StaticStore<N, A, ID>::~StaticStore() {}

        /**
         *  @brief Initialize the data store.
         *  @todo This will likely NOT work on MSVC.
         */
        template<size_t N, short A, int ID>
        uint8_t StaticStore<N, A, ID>::_store[] {};

        template<size_t N, short A, int ID>
        inline uint8_t* StaticStore<N, A, ID>::getRawStorage() {
            return &(this->_store[0]);
        }
    }
}
