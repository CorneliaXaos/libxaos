#ifndef     LIBXAOS_CORE_POINTERS_INTERNAL_CONTROLBLOCK_H
#define     LIBXAOS_CORE_POINTERS_INTERNAL_CONTROLBLOCK_H

namespace libxaos {
    namespace pointers {
        namespace internal { // an extra namespace.. just to deter outside use

            enum PointerType {
                PLAIN_TYPE,
                ARRAY_TYPE
            };

            class ControlBlock {

                public:
                    //! Constructs a ControlBlock from a void pointer and the
                    //! PointerType (Plain or Array)
                    ControlBlock(void*, PointerType);
                    ~ControlBlock();

                    //! Should not be copy constructed
                    ControlBlock(const ControlBlock&) = delete;
                    //! Should not be copy assigned
                    ControlBlock& operator=(const ControlBlock&) = delete;
                    //! Should not be move constructed
                    ControlBlock(ControlBlock&&) = delete;
                    //! Should not be move assigned.
                    CotnrolBlock& operator=(ControlBlock&&) = delete;

                    //! Returns a StrongPointer
                    template<typename T>
                    StrongPointer<T>

                private:
                    void* _pointer;
                    PointerType _type;
                    int _strongReferences;
                    int _weakReferences;

            };

        }
    }
}

#endif   // LIBXAOS_CORE_POINTERS_INTERNAL_CONTROLBLOCK_H
