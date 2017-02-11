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
         */
        template<size_t N, short A, int ID>
        #ifdef _MSC_VER // GODDAMIT MICROSOFT....  FOLLOW THE STANDARD...
            uint8_t StaticStore<N, A, ID>::_store[] = "";
        #else
            uint8_t StaticStore<N, A, ID>::_store[] {};
        #endif

        template<size_t N, short A, int ID>
        inline uint8_t* StaticStore<N, A, ID>::getRawStorage() {
            return &(this->_store[0]);
        }
    }
}
