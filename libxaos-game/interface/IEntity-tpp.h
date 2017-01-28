/**
 *  @file IEntity-tpp.h
 *  @brief Implementations for the IEntity template class
 */

 #include <utility>

 namespace libxaos {
    namespace game {

        template<typename T, int N>
        uintmax_t IEntity<T, N>::acquireID() {
            static uintmax_t entity_count = 0;
            entity_count++;
            #ifdef _DEBUG
                if (entity_count == 0) {
                    //! @todo debug emit that entity IDs have looped.
                }
            #endif
            return entity_count;
        }

        // Constructors
        template<typename T, int N>
        IEntity<T, N>::IEntity() : IEntity<T,N>("", Vector<T, N>{}) {}
        template<typename T, int N>
        IEntity<T, N>::IEntity(const std::string& name) :
                IEntity<T, N>(name, Vector<T, N>{}) {}
        template<typename T, int N>
        IEntity<T, N>::IEntity(const Vector<T, N>& position) :
                IEntity<T, N>("", position) {}
        template<typename T, int N>
        IEntity<T, N>::IEntity(const std::string& name,
                const Vector<T, N>& position) : _name(name),
                _position(position), _entityID(acquireID()) {}
        template<typename T, int N>
        IEntity<T, N>::~IEntity() {} // nothing to clean up

        // Copy / Move Semantics
        template<typename T, int N>
        IEntity<T, N>::IEntity(const IEntity& other) :
                IEntity<T,N>(other._name, other._position) {}
        template<typename T, int N>
        IEntity<T, N>& IEntity<T, N>::operator=(const IEntity& other) {
            if (this != &other) {
                _name = other._name;
                _position = other._postion;
            }
            return *this;
        }
        template<typename T, int N>
        IEntity<T, N>::IEntity(IEntity&& other) : _name(std::move(other._name)),
                _position(std::move(other._position)),
                _entityID(acquireID()) {}
        template<typename T, int N>
        IEntity<T, N>& IEntity<T, N>::operator=(IEntity&& other) {
            if (this != &other) {
                _name = std::move(other._name);
                _position = std::move(other._position);
            }
            return *this;
        }

        // Name Accessors
        template<typename T, int N>
        inline void IEntity<T, N>::setName(const std::string& name) {
            _name = name;
        }
        template<typename T, int N>
        inline std::string IEntity<T, N>::getName() const {
            return _name;
        }

        // Position Accessors
        template<typename T, int N>
        inline void IEntity<T, N>::setPosition(const Vector<T, N>& position) {
            _position = position;
        }
        template<typename T, int N>
        inline Vector<T, N> IEntity<T, N>::getPosition() const {
            return _position;
        }

        // (In)Equality Operators
        template<typename T, int N>
        inline bool operator==(const IEntity<T, N>& a, const IEntity<T, N>& b) {
            return a._entityID == b._entityID; // friend access
        }
        template<typename T, int N>
        inline bool operator!=(const IEntity<T, N>& a, const IEntity<T, N>& b) {
            return !(a == b);
        }
    }
 }
