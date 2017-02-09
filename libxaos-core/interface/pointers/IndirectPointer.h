// WARNING - NOT IMPLEMENTED YET (AND WON'T BE FOR SOME TIME)

#ifndef     LIBXAOS_CORE_POINTERS_INDIRECT_POINTER_H
#define     LIBXAOS_CORE_POINTERS_INDIRECT_POINTER_H

#include <cstddef>
#include <type_traits>

namespace libxaos {
    namespace pointers {

        /**
         *  @brief Allows access to a specific pointer without concerns of
         *  ownership.
         *
         *  This pointer class allows one to delegate access to a pointer
         *  without counting references or such.  Because of this, users need
         *  to be wary of the targeted pointer's lifecycle and carefully
         *  consider who they lend an IndirectPointer to.  (Future
         *  implementations of this class may allow the attachment of a callback
         *  which can be used to verify if the held pointer is still valid.)
         *
         *  This IndirectPointer only supports non-array types!  Please
         *  see IndirectArrayPointer for an Array variant!
         *
         *  @tparam T the type of pointer to hold.
         */
        template<typename T>
        class IndirectPointer {
            static_assert(!std::is_array<T>::value,
                    "This IndirectPointer doesn't support array types!");

            //! Typename needed to allow const protection of member types.
            using PointerType = typename std::remove_cv<T>::type*;

            public:
                IndirectPointer();
                //! Construct this indirect pointer from the supplied T*
                explicit IndirectPointer(PointerType);
                //! Constructs a nullptr IndirectPointer from type
                IndirectPointer(nullptr_t);
                ~IndirectPointer();

                IndirectPointer(const IndirectPointer<T>&);
                IndirectPointer<T>& operator=(const IndirectPointer<T>&);
                IndirectPointer(IndirectPointer<T>&&);
                IndirectPointer<T>& operator=(IndirectPointer<T>&&);

                //! Allow assigning nullptr to this IndirectPointer
                IndirectPointer<T>& operator=(nullptr_t);

                //! Arrow Operator Dereferencing
                inline T* operator->() const;
                //! Asterisk Operator Dereferencing
                inline T& operator*() const;

                //! Returns true if the internal pointer is not null
                inline operator bool() const;

                //! Compare (Equality) to nullptr
                inline bool operator==(nullptr_t) const;
                //! Compare (Inequality) to nullptr
                inline bool operator!=(nullptr_t) const;
                //! Compare (Equality) to another IndirectPointer
                inline bool operator==(const IndirectPointer<T>&) const;
                //! Compare (Inequality) to another IndirectPointer
                inline bool operator!=(const IndirectPointer<T>&) const;

            private:
                PointerType _pointer;
        };

    }
}

#endif   // LIBXAOS_CORE_POINTERS_INDIRECT_POINTER_H
