/**
 *  @file IEntityController-tpp.h
 *  @brief Implementations for the IEntityController template class
 */

 namespace libxaos {
    namespace game {

        // Constructors
        template<typename T, int N>
        IEntityController<T, N>::IEntityController() :
                IEntityController<T, N>(nullptr) {}
        template<typename T, int N>
        IEntityController<T, N>::IEntityController(
                WeakEntityPointer<T, N> entPtr) : _entity(entPtr) {}
        template<typename T, int N>
        IEntityController<T, N>::~IEntityController() {} // Nothing to do

        // Copy / Move Semantics
        template<typename T, int N>
        IEntityController<T, N>::IEntityController(
                const IEntityController<T, N>& other) :
                _entity(other._entity) {}
        template<typename T, int N>
        IEntityController<T, N>& IEntityController<T, N>::operator=(
                const IEntityController<T, N>& other) {
            if (this != &other) {
                _entity = other._entity;
            }
            return *this;
        }
        template<typename T, int N>
        IEntityController<T, N>::IEntityController(
                IEntityController<T, N>&& other) : _entity(other._entity) {
            other._entity = nullptr;
        }
        template<typename T, int N>
        IEntityController<T, N>& IEntityController<T, N>::operator=(
                IEntityController<T, N>&& other) {
            if (this != &other) {
                _entity = other._entity;
                other._entity = nullptr;
            }
            return *this;
        }

        // Entity Accessors
        template<typename T, int N>
        void IEntityController<T, N>::setEntity(
                WeakEntityPointer<T, N> entPtr) {
            _entity = entPtr;
        }
        template<typename T, int N>
        WeakEntityPointer<T, N> IEntityController<T, N>::getEntity() const {
            return _entity;
        }
    }
 }
