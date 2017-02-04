#ifndef     LIBXAOS_CORE_POINTERS_INTERNAL_CONTROLBLOCK_H
#define     LIBXAOS_CORE_POINTERS_INTERNAL_CONTROLBLOCK_H

namespace libxaos {
    namespace pointers {
        namespace internal { // an extra namespace.. just to deter outside use

            //! An enum for differentiating between owners and observers
            enum ReferenceType {
                STRONG,
                WEAK
            };

            //! An enum for differentiating between pointer types.
            enum PointerType {
                PLAIN,
                ARRAY
            };

            /**
             *  @brief A ControlBlock handles the lifetime of a shared pointer.
             *
             *  THIS CLASS IS INTERNAL ONLY.  YOU SHOULD NOT BE USING IT.
             *
             *  A ControlBlock manages the lifetime of a shared pointer based on
             *  registered Strong and Weak references.  It deletes the held
             *  pointer based on those referencing itself.  Additionally, it
             *  manages its own lifetime and will destroy itself when there are
             *  no longer any shared pointers utilizing it.
             */
            template<typename T, PointerType P>
            class ControlBlock {

                public:

                    //! Create a ControlBlock*
                    static inline ControlBlock<T, P>* create(T*);
                    ~ControlBlock();

                    //! Should not be copy constructed
                    ControlBlock(const ControlBlock<T, P>&) = delete;
                    //! Should not be copy assigned
                    ControlBlock<T, P>& operator=(const ControlBlock<T, P>&)
                            = delete;
                    //! Should not be move constructed
                    ControlBlock(ControlBlock<T, P>&&) = delete;
                    //! Should not be move assigned.
                    ControlBlock<T, P>& operator=(ControlBlock<T, P>&&)
                            = delete;

                    //! Returns the pointer
                    inline T* getPointer() const;

                    //! Increment reference
                    void incrementReference(ReferenceType);
                    //! Decrement reference
                    void decrementReference(ReferenceType);

                    //! Validates the internal pointer to be non-null
                    inline operator bool() const;

                private:

                    //! Constructs a ControlBlock from a T* .  This constructor
                    //! is private since it shouldn't be stack allocated.
                    ControlBlock(T*);
                    //! Deletes the internal pointer
                    inline void deletePointer();

                    //! The held pointer
                    T* _pointer;
                    //! The number of strong shared pointers using this block.
                    int _strongReferences;
                    //! The number of weak shared pointers using this block.
                    int _weakReferences;
            };

        }
    }
}

// Pull in implementations
#include "ControlBlock-tpp.h"

#endif   // LIBXAOS_CORE_POINTERS_INTERNAL_CONTROLBLOCK_H
