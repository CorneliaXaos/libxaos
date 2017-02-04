#ifndef     LIBXAOS_CORE_POINTERS_SHARED_POINTERS_H
#define     LIBXAOS_CORE_POINTERS_SHARED_POINTERS_H

#include <cstddef>
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
                explicit StrongPointer(T*);
                //! Constructs a nullptr StrongPointer from type
                StrongPointer(nullptr_t);
                ~StrongPointer();

                StrongPointer(const StrongPointer<T>&);
                StrongPointer<T>& operator=(const StrongPointer<T>&);
                StrongPointer(StrongPointer<T>&&);
                StrongPointer<T>& operator=(StrongPointer<T>&&);

                //! Allows assigning nullptr to a StrongPointer
                StrongPointer<T>& operator=(nullptr_t);

                //! Arrow Operator Dereferencing
                inline T* operator->() const;
                //! Asterisk Operator Dereferencing
                inline T& operator*() const;

                //! Returns true if the internal pointer is not null
                inline operator bool() const;

                //! Converts this StrongPointer to a WeakPointer
                inline WeakPointer<T> getWeakPointer() const;

                //! Compare (Equality) to nullptr
                inline bool operator==(nullptr_t);
                //! Compare (Inequality) to nullptr
                inline bool operator!=(nullptr_t);
                //! Compare (Equality) to another StrongPointer
                inline bool operator==(const StrongPointer<T>&);
                //! Compare (Inequality) to another StrongPointer
                inline bool operator!=(const StrongPointer<T>&);
                //! Compare (Equality) to a WeakPointer
                inline bool operator==(const WeakPointer<T>&);
                //! Compare (Inequality) to a WeakPointer
                inline bool operator!=(const WeakPointer<T>&);

                // INTERNAL CONSTRUCTORS

                //! Constructs a StrongPointer from a provided ControlBlock
                //! If the ControlBlock is null or invalid, this StrongPointer
                //! Points to a nullptr
                StrongPointer(ControlBlock<T, PointerType::PLAIN>*);

            private:
                //! The data block used to Control access to the pointer.
                ControlBlock<T, PointerType::PLAIN>* _block;
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
                //! Constructs a nullptr WeakPointer from type
                WeakPointer(nullptr_t);
                ~WeakPointer();

                WeakPointer(const WeakPointer<T>&);
                WeakPointer<T>& operator=(const WeakPointer<T>&);
                WeakPointer(WeakPointer<T>&&);
                WeakPointer<T>& operator=(WeakPointer<T>&&);

                //! Allows assigning nullptr to a WeakPointer
                WeakPointer<T>& operator=(nullptr_t);

                //! Returns true if the internal pointer is not null
                inline operator bool() const;

                //! Converts this WeakPointer to a StrongPointer
                inline StrongPointer<T> getStrongPointer() const;

                //! Compare (Equality) to nullptr
                inline bool operator==(nullptr_t);
                //! Compare (Inequality) to nullptr
                inline bool operator!=(nullptr_t);
                //! Compare (Equality) to a StrongPointer
                inline bool operator==(const StrongPointer<T>&);
                //! Compare (Inequality) to a StrongPointer
                inline bool operator!=(const StrongPointer<T>&);
                //! Compare (Equality) to another WeakPointer
                inline bool operator==(const WeakPointer<T>&);
                //! Compare (Inequality) to another WeakPointer
                inline bool operator!=(const WeakPointer<T>&);

                // INTERNAL CONSTRUCTORS

                //! Constructs a WeakPointer from a provided ControlBlock
                //! If the ControlBlock is null or invalid, this WeakPointer
                //! Points to a nullptr
                WeakPointer(ControlBlock<T, PointerType::PLAIN>*);

            private:
                //! The data block used to control access to the pointer.
                ControlBlock<T, PointerType::PLAIN>* _block;
        };
    }
}

// Pull in implementations
#include "shared_pointers-tpp.h"

#endif   // LIBXAOS_CORE_POINTERS_SHARED_POINTERS_H
