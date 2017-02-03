#ifndef     LIBXAOS_CORE_POINTERS_SHARED_POINTERS_H
#define     LIBXAOS_CORE_POINTERS_SHARED_POINTERS_H

#include <type_traits>

#include "pointers/__internal__/ControlBlock.h"

namespace libxaos {
    namespace pointers {

        namespace {
            using namespace internal; // Grab that internal code!
        }

        // Forward declare our WeakPointer
        template<typename T>
        class WeakPointer;

        /**
         *  @brief A StrongPointer mirrors the functionality of a
         *  std::shared_ptr.
         *
         *  The only (primary) difference between this class and
         *  std::shared_ptr is the name is more parallel with its
         *  WeakPointer (std::weak_ptr) cousin.
         *
         *  This StrongPointer only supports non-array type allocations!  Please
         *  see StrongArrayPointer for an Array variant!
         */
        template<typename T>
        class StrongPointer {
            static_assert(!std::is_array<T>::value,
                    "This StrongPointer doesn't support array types!");

            public:
                //! Constructs a "null" StrongPointer
                StrongPointer();
                //! Constructs a StrongPointer from the provided pointer.
                StrongPointer(T*);
                ~StrongPointer();

                StrongPointer(const StrongPointer<T>&);
                StrongPointer<T>& operator=(const StrongPointer<T>&);
                StrongPointer(StrongPointer<T>&&);
                StrongPointer<T>& operator=(StrongPointer<T>&&);

                //! Arrow Operator Dereferencing
                inline T* operator->() const;
                //! Asterisk Operator Dereferencing
                inline T& operator*() const;

                //! Returns true if the internal pointer is not null
                inline bool operator bool() const;

                //! Converts this StrongPointer to a WeakPointer
                WeakPointer<T> getWeakPointer();

                // INTERNAL CONSTRUCTORS

                //! Constructs a StrongPointer from a provided ControlBlock
                //! If the ControlBlock is null or invalid, this StrongPointer
                //! Points to a nullptr
                StrongPointer(ControlBlock*);

            private:
                //! The data block used to Control access to the pointer.
                ControlBlock* _block;
        };

        /**
         *  @brief A WeakPointer mirrors the functionality of a std::weak_ptr.
         *
         *  There are few differences between this pointer and the STL
         *  provided variant (beyond interface, level of testing, and available
         *  manipulations).  It should function, at a basal level, similar to
         *  std::weak_ptr.
         *
         *  This WeakPointer only supports non-array type allocations!  Please
         *  see WeakArrayPointer for an Array variant!
         */
        template<typename T>
        class WeakPointer {
            static_assert(!std::is_array<T>::value,
                    "This WeakPointer doesn't support array types!");

            public:
                //! Constructs a "null" WeakPointer
                WeakPointer();
                ~WeakPointer();

                WeakPointer(const WeakPointer<T>&);
                WeakPointer<T>& operator=(const WeakPointer<T>&);
                WeakPointer(WeakPointer<T>&&);
                WeakPointer<T>& operator=(WeakPointer<T>&&);

                //! Returns true if the internal pointer is not null
                inline bool operator bool() const;

                //! Converts this WeakPointer to a StrongPointer
                StrongPointer<T> getStrongPointer();

                // INTERNAL CONSTRUCTORS

                //! Constructs a WeakPointer from a provided ControlBlock
                //! If the ControlBlock is null or invalid, this WeakPointer
                //! Points to a nullptr
                WeakPointer(ControlBlock*);

            private:
                //! The data block used to control access to the pointer.
                ControlBlock* _block;
        };
    }
}

// Pull in implementations
#include "shared_pointers-tpp.h"

#endif   // LIBXAOS_CORE_POINTERS_SHARED_POINTERS_H
