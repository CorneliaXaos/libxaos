#ifndef     LIBXAOS_CORE_POINTERS_INTERNAL_CONTROLBLOCK_H
#define     LIBXAOS_CORE_POINTERS_INTERNAL_CONTROLBLOCK_H

namespace libxaos {
    namespace pointers {
        namespace internal { // an extra namespace.. just to deter outside use

            template<typename T>
            class ControlBlock {

                public:

                    enum ReferenceType {
                        STRONG,
                        WEAK
                    };

                    //! Constructs a ControlBlock from a T pointer
                    ControlBlock(T*);
                    ~ControlBlock();

                    //! Should not be copy constructed
                    ControlBlock(const ControlBlock<T>&) = delete;
                    //! Should not be copy assigned
                    ControlBlock<T>& operator=(const ControlBlock<T>&) = delete;
                    //! Should not be move constructed
                    ControlBlock(ControlBlock<T>&&) = delete;
                    //! Should not be move assigned.
                    CotnrolBlock<T>& operator=(ControlBlock<T>&&) = delete;

                    //! Returns the pointer
                    T* getPointer() const;

                    //! Increment reference
                    void incrementReference(ReferenceType);
                    //! Decrement reference
                    void decrementReference(ReferenceType);

                private:
                    T* _pointer;
                    int _strongReferences;
                    int _weakReferences;
            };

        }
    }
}

// Pull in implementations
#include "ControlBlock-tpp.h"

#endif   // LIBXAOS_CORE_POINTERS_INTERNAL_CONTROLBLOCK_H
