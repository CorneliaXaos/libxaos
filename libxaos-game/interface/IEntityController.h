#ifndef     LIBXAOS_GAME_IENTITYCONTROLLER_H
#define     LIBXAOS_GAME_IENTITYCONTROLLER_H

#include <type_traits>

#include "pointers/shared_pointers.h"

namespace libxaos {
    namespace game {

        // Forward declare our pointer type
        template<typename T, int N>
        class IEntity;

        namespace {
            template<typename T, int N>
            using WeakEntityPointer =
                    libxaos::pointers::WeakPointer<IEntity<T, N>>;
        }

        /**
         *  @brief This class is used to control an IEntity instance.
         *
         *  This class controls an attached IEntity via it's update function.
         *  Since it manipulates an IEntity it needs to be configured to
         *  manipulate IEntities of particular dimension type and dimension
         *  size.
         *
         *  @tparam T the numeric type to measure distance in each dimension.
         *  @tparam N the number of dimensions the world contains.
         */
        template<typename T, int N>
        class IEntityController {
            static_assert(std::is_arithmetic<T>::value,
                    "The world's dimension type must be arithmetic!");

            public:
                IEntityController();
                //! Construct this controller and attach the provided entity.
                IEntityController(WeakEntityPointer<T, N>);
                virtual ~IEntityController();

                IEntityController(const IEntityController<T, N>&);
                IEntityController<T, N>& operator=(
                        const IEntityController<T, N>&);
                IEntityController(IEntityController&&);
                IEntityController<T, N>& operator=(IEntityController<T, N>&&);

                //! Sets (attaches) an Entity to this controller.
                inline void setEntity(WeakEntityPointer<T, N>);
                //! Gets the attached entity.
                inline WeakEntityPointer<T, N> getEntity() const;

                //! Updates the attached entity.
                virtual void update() const = 0;

            private:
                //! A shared pointer to the attached entity.
                WeakEntityPointer<T, N> _entity;
        };

    }
}

// Pull in implementations
#include "IEntityController-tpp.h"

#endif   // LIBXAOS_GAME_IENTITYCONTROLLER_H
