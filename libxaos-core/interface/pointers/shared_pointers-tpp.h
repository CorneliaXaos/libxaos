/**
 *  @file shared_pointers-tpp.h
 *  @brief Implementations for: libxaos-core:pointers/shared_pointers.h
 *
 *  This file provides template implementations for StrongPointer and
 *  WeakPointer (defined in shared_pointers.h).
 *
 *  Curiously, these two classes implementations are nearly identical...
 *  They probably could be coalesced into a single class (SharedPointer) and
 *  using the ReferenceType enum from ControlBlock be differentiated
 *  appropriately.  (Would also need an enable_if or two..)
 */

#include <cassert>
#include <utility>

namespace libxaos {
    namespace pointers {

        //// StrongPointer
        // Constructors
        template<typename T>
        StrongPointer<T>::StrongPointer() : _block(nullptr) {}
        template<typename T>
        StrongPointer<T>::StrongPointer(T* pointer) :
                _block(ControlBlock<T, PointerType::PLAIN>::create(pointer)) {
            _block->incrementReference(ReferenceType::STRONG);
        }
        template<typename T>
        StrongPointer<T>::StrongPointer(nullptr_t) : _block(nullptr) {}
        template<typename T>
        StrongPointer<T>::~StrongPointer() {
            if (_block) {
                _block->decrementReference(ReferenceType::STRONG);
                _block = nullptr; // Probably not needed.
            }
        }

        // Copy and Move Semantics
        template<typename T>
        StrongPointer<T>::StrongPointer(const StrongPointer<T>& other) :
                StrongPointer<T>(other._block) {} // delegate
        template<typename T>
        StrongPointer<T>& StrongPointer<T>::operator=(
                const StrongPointer<T>& other) {
            if (this != &other) {
                // Check to make sure that our current reference is decremented
                if (_block)
                    _block->decrementReference(ReferenceType::STRONG);

                // Copy manually and increment if needed
                _block = other._block;
                if (_block)
                    _block->incrementReference(ReferenceType::STRONG);
            }
            return *this;
        }
        template<typename T>
        StrongPointer<T>::StrongPointer(StrongPointer<T>&& other) :
                _block(other._block) {
            // Copy and then null on dying instance of class
            other._block = nullptr;
        }
        template<typename T>
        StrongPointer<T>& StrongPointer<T>::operator=(
                StrongPointer<T>&& other) {
            if (this != &other) {
                // This swap works perfectly.  Teh dying reference will
                // decrease the original _block this one had assuming it wasn't
                // nullptr (if it was the dying reference does nothing)
                std::swap(_block, other._block);
            }
            return *this;
        }

        // Nullptr assignment
        template<typename T>
        StrongPointer<T>& StrongPointer<T>::operator=(nullptr_t) {
            if (_block) {
                _block->decrementReference(ReferenceType::STRONG);
                _block = nullptr;
            }
            return *this;
        }

        // Dereference Operators (Assumes block is valid AND pointer is valid)
        // It should always be valid for StrongPointers holding a non-null
        // ControlBlock pointer.
        template<typename T>
        inline T* StrongPointer<T>::operator->() const {
            assert(*this);
            return _block->getPointer();
        }
        template<typename T>
        inline T& StrongPointer<T>::operator*() const {
            assert(*this);
            return *(_block->getPointer());
        }

        // operator bool()
        template<typename T>
        inline StrongPointer<T>::operator bool() const {
            return _block && *_block;
        }

        // WeakPointer conversion
        template<typename T>
        inline WeakPointer<T> StrongPointer<T>::getWeakPointer() const {
            return WeakPointer<T>{_block};
        }

        // Comparison Operators
        template<typename T>
        inline bool StrongPointer<T>::operator==(nullptr_t) {
            return _block == nullptr;
        }
        template<typename T>
        inline bool StrongPointer<T>::operator!=(nullptr_t) {
            return _block != nullptr;
        }
        template<typename T>
        inline bool StrongPointer<T>::operator==(
                const StrongPointer<T>& other) {
            return _block == other._block;
        }
        template<typename T>
        inline bool StrongPointer<T>::operator!=(
                const StrongPointer<T>& other) {
            return _block != other._block;
        }
        template<typename T>
        inline bool StrongPointer<T>::operator==(
                const WeakPointer<T>& other) {
            return _block == other.getStrongPointer()._block;
        }
        template<typename T>
        inline bool StrongPointer<T>::operator!=(
                const WeakPointer<T>& other) {
            return _block != other.getStrongPointer()._block;
        }

        // Internal Constructor, assumes it's being passed a valid block
        template<typename T>
        StrongPointer<T>::StrongPointer(
                ControlBlock<T, PointerType::PLAIN>* block) : _block(block) {
            if (_block)
                _block->incrementReference(ReferenceType::STRONG);
        }

        //// WeakPointer
        // Constructors
        template<typename T>
        WeakPointer<T>::WeakPointer() : _block(nullptr) {}
        template<typename T>
        WeakPointer<T>::WeakPointer(nullptr_t) : _block(nullptr) {}
        template<typename T>
        WeakPointer<T>::~WeakPointer() {
            if (_block) {
                _block->decrementReference(ReferenceType::WEAK);
                _block = nullptr; // probably unnecessary
            }
        }

        // Copy / Move Semantics
        template<typename T>
        WeakPointer<T>::WeakPointer(const WeakPointer<T>& other) :
                WeakPointer<T>(other._block) {}
        template<typename T>
        WeakPointer<T>& WeakPointer<T>::operator=(
                const WeakPointer<T>& other) {
            if (this != & other) {
                // Check to make sure that our current reference is decremented
                if (_block)
                    _block->decrementReference(ReferenceType::WEAK);

                // Copy manually and increment if needed
                _block = other._block;
                if (_block)
                    _block->incrementReference(ReferenceType::WEAK);
            }
            return *this;
        }
        template<typename T>
        WeakPointer<T>::WeakPointer(WeakPointer<T>&& other) :
                _block(other._block) {
            // Copy and then null on dying instance of class
            other._block = nullptr;
        }
        template<typename T>
        WeakPointer<T>& WeakPointer<T>::operator=(
                WeakPointer<T>&& other) {
            if (this != &other) {
                // This swap works perfectly.  Teh dying reference will
                // decrease the original _block this one had assuming it wasn't
                // nullptr (if it was the dying reference does nothing)
                std::swap(_block, other._block);
            }
            return *this;
        }

        // nullptr assignment
        template<typename T>
        WeakPointer<T>& WeakPointer<T>::operator=(nullptr_t) {
            if (_block) {
                _block->decrementReference(ReferenceType::WEAK);
                _block = nullptr;
            }
            return *this;
        }

        // operator bool()
        template<typename T>
        inline WeakPointer<T>::operator bool() const {
            return _block && *_block;
        }

        // StrongPointer conversion
        template<typename T>
        inline StrongPointer<T> WeakPointer<T>::getStrongPointer() const {
            if (*this)
                return StrongPointer<T>{_block};
            else
                return StrongPointer<T>{nullptr};
        }

        // Comparison Operators
        template<typename T>
        inline bool WeakPointer<T>::operator==(nullptr_t) {
            return _block == nullptr;
        }
        template<typename T>
        inline bool WeakPointer<T>::operator!=(nullptr_t) {
            return _block != nullptr;
        }
        template<typename T>
        inline bool WeakPointer<T>::operator==(
                const StrongPointer<T>& other) {
            return _block == other.getWeakPointer()._block;
        }
        template<typename T>
        inline bool WeakPointer<T>::operator!=(
                const StrongPointer<T>& other) {
            return _block != other.getWeakPointer()._block;
        }
        template<typename T>
        inline bool WeakPointer<T>::operator==(
                const WeakPointer<T>& other) {
            return _block == other._block;
        }
        template<typename T>
        inline bool WeakPointer<T>::operator!=(
                const WeakPointer<T>& other) {
            return _block != other._block;
        }

        // Internal Constructor
        template<typename T>
        WeakPointer<T>::WeakPointer(ControlBlock<T, PointerType::PLAIN>* block)
                : _block(block) {
            if (_block)
                _block->incrementReference(ReferenceType::WEAK);
        }
    }
}
