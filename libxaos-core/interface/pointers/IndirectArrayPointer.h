// WARNING - NOT IMPLEMENTED YET (AND WON'T BE FOR SOME TIME)

#ifndef     LIBXAOS_CORE_POINTERS_INDIRECT_POINTER_H
#define     LIBXAOS_CORE_POINTERS_INDIRECT_POINTER_H

#include <cstddef>
#include <type_traits>

namespace libxaos {
    namespace pointers {

        /**
         *  @brief Allows access to a specific array pointer without concerns of
         *  ownership.
         *
         *  This pointer class allows one to delegate access to a pointer
         *  without counting references or such.  Because of this, users need
         *  to be wary of the targeted pointer's lifecycle and carefully
         *  consider who they lend an IndirectPointer to.  (Future
         *  implementations of this class may allow the attachment of a callback
         *  which can be used to verify if the held pointer is still valid.)
         *
         *  This IndirectPointer only supports array types!  Please see
         *  IndirectPointer for a plain variant!
         *
         *  @tparam T the type of pointer to hold.
         */
        template<typename T>
        class IndirectArrayPointer {

            //! Typename needed to allow const protection of member types.
            using PointerType = typename std::remove_cv<T>::type*;

            public:
                IndirectArrayPointer();
                //! Construct this pointer from the supplied T* and size
                explicit IndirectArrayPointer(PointerType, int);
                //! Constructs a nullptr IndirectPointer from type
                IndirectArrayPointer(nullptr_t);
                ~IndirectArrayPointer();

                IndirectArrayPointer(const IndirectArrayPointer<T>&);
                IndirectArrayPointer<T>& operator=(
                        const IndirectArrayPointer<T>&);
                IndirectArrayPointer(IndirectArrayPointer<T>&&);
                IndirectArrayPointer<T>& operator=(IndirectArrayPointer<T>&&);

                //! Allow assigning nullptr to this IndirectPointer
                IndirectArrayPointer<T>& operator=(nullptr_t);

                //! Array Dereferencing
                inline T operator[](int) const;
                //! Array Dereferencing (length checked)
                inline T at(int) const;

                //! Returns the size of the held array pointer
                inline int getSize() const;

                //! Returns true if the internal pointer is not null
                inline operator bool() const;

                //! Compare (Equality) to nullptr
                inline bool operator==(nullptr_t) const;
                //! Compare (Inequality) to nullptr
                inline bool operator!=(nullptr_t) const;
                //! Compare (Equality) to another IndirectPointer
                inline bool operator==(const IndirectArrayPointer<T>&) const;
                //! Compare (Inequality) to another IndirectPointer
                inline bool operator!=(const IndirectArrayPointer<T>&) const;

            private:
                PointerType _pointer;
                int _size;
        };

    }
}

#endif   // LIBXAOS_CORE_POINTERS_INDIRECT_POINTER_H

