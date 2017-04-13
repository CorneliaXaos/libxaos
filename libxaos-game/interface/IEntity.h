#ifndef     LIBXAOS_GAME_IENTITY_H
#define     LIBXAOS_GAME_IENTITY_H

#include <cstdint>
#include <string>
#include <type_traits>

#include "linear/Vector.h"

namespace libxaos {
    namespace game {

        namespace {

            template<typename T, int N>
            using Vector = libxaos::linear::Vector<T, N>;
        }

        /**
         *  @brief This class represents a Positional Entity within the game
         *      world.
         *
         *  This class represents an entity that can be positioned in the game
         *  world.  They type of positioning is entirely dependent on the
         *  template parameters of this class.
         *
         *  These entities have two public data points:
         *      - std::string - Name - DOES NOT NEED TO BE UNIQUE!
         *      - Vector<T, N> - Position - Location in the Game World.
         *
         *  @tparam T the numeric type to measure distance in each dimension.
         *  @tparam N the number of dimensions this world contains.
         */
        template<typename T, int N>
        class IEntity {
            static_assert(std::is_arithmetic<T>::value,
                    "The world's dimension type must be arithmetic!");

            public:
                IEntity();
                //! Construct this Entity with the provided name.
                explicit IEntity(const std::string&);
                //! Construct this Entity with the provided position.
                explicit IEntity(const Vector<T, N>&);
                //! Construct this Entity with the provided name and position.
                IEntity(const std::string&, const Vector<T, N>&);
                virtual ~IEntity();

                IEntity(const IEntity&);
                IEntity& operator=(const IEntity&);
                IEntity(IEntity&&);
                IEntity& operator=(IEntity&&);

                //! Sets the name of this entity.
                inline void setName(const std::string&);
                //! Gets the name of this entity.
                inline std::string getName() const;

                //! Sets the position of this entity.
                inline void setPosition(const Vector<T, N>&);
                //! Gets the position of this entity.
                inline Vector<T, N> getPosition() const;

            private:
                //! The name of this entity.
                std::string _name;
                //! The position of this entity.
                Vector<T, N> _position;

                //! @todo replace this faulty system with a real uuid system
                //! This entity's ID as computed by a global static variable.
                uintmax_t _entityID;

                //! Used by instances to acquire a UUID
                static uintmax_t acquireID();

                //! Allow the equality operator to access _entityID
                template<typename S, int M>
                friend bool operator==(const IEntity<S, M>&,
                        const IEntity<S, M>&);
        };

        //! Equality Comparison of IEntity instances.
        template<typename T, int N>
        inline bool operator==(const IEntity<T, N>&, const IEntity<T, N>&);
        //! Inequality Comparison of IEntity instances.
        template<typename T, int N>
        inline bool operator!=(const IEntity<T, N>&, const IEntity<T, N>&);
    }
}

// Pull in implementations
#include "IEntity-tpp.h"

#endif   // LIBXAOS_GAME_IENTITY_H
