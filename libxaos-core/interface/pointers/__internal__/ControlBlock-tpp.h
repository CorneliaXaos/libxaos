/**
 *  @file ControlBlock-tpp.h
 *  @brief Implementations for: libxaos-core:pointers/__internal__/ControlBlock.h
 *
 *  This file provides implementations for the ControlBlock class.
 */

#include <cassert>

namespace libxaos {
    namespace pointers {
        namespace internal {

            template<typename T, PointerType P>
            inline ControlBlock<T, P>* ControlBlock<T, P>::
                    create(T* pointer) {
                return new ControlBlock<T, P>(pointer);
            }
            template<typename T, PointerType P>
            ControlBlock<T, P>::~ControlBlock() {
                assert(_strongReferences == 0);
                assert(_weakReferences == 0);

                deletePointer();
            }

            template<typename T, PointerType P>
            inline T* ControlBlock<T, P>::getPointer() const {
                return _pointer;
            }

            template<typename T, PointerType P>
            inline void ControlBlock<T, P>::incrementReference(
                    ReferenceType type) {
                if (type == ReferenceType::STRONG) {
                    _strongReferences++;
                } else { // if (type == ReferenceType::WEAK)
                    _weakReferences++;
                }
            }
            template<typename T, PointerType P>
            inline void ControlBlock<T, P>::decrementReference(
                    ReferenceType type) {
                if (type == ReferenceType::STRONG) {
                    _strongReferences--;
                    if (_strongReferences <= 0) { // just being safe
                        deletePointer();
                        if (_weakReferences <= 0) { // just being safe
                            delete this;
                        }
                    }
                } else { // if (type == ReferenceType::WEAK)
                    _weakReferences--;
                    if (_weakReferences <= 0 && _strongReferences <= 0) {
                        delete this;
                    }
                }
            }

            template<typename T, PointerType P>
            inline ControlBlock<T, P>::operator bool() const {
                return _pointer;
            }

            // It'll be up to the users to make sure the initialize the strong
            // reference count to 1.
            template<typename T, PointerType P>
            ControlBlock<T, P>::ControlBlock(T* pointer) : _pointer(pointer),
                    _strongReferences(0), _weakReferences(0) {}

            template<typename T, PointerType P>
            inline void ControlBlock<T, P>::deletePointer() {
                if (_pointer) {
                    if (P == PointerType::PLAIN) {
                        delete _pointer;
                    } else { // if (P == PointerType::ARRAY)
                        delete[] _pointer;
                    }
                    _pointer = nullptr;
                }
            }
        }
    }
}
