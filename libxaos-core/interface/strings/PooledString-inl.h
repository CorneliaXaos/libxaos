/**
 *  @file PooledString-inl.h
 *  @brief Inline implements: libxaos-core:strings/PooledString.h
 *
 *  This file provides inline implementations for the PooledString class.
 */

namespace libxaos {
    namespace strings {

        // Conversion operators
        inline PooledString::operator bool() const {
            return _string != nullptr;
        }

        // getCharPointer (not really much else to explain this "class" of
        // functions. :P
        inline const char* PooledString::getCharPointer() const {
            return _string;
        }

        // Comparison operators - a lot of these depend on each other
        inline bool operator==(const PooledString& a, const PooledString& b) {
            return a.getCharPointer() == b.getCharPointer();
        }
        inline bool operator!=(const PooledString& a, const PooledString& b) {
            return !(a == b);
        }
        inline bool operator==(const PooledString& str, nullptr_t) {
            return str.getCharPointer() == nullptr;
        }
        inline bool operator==(nullptr_t, const PooledString& str) {
            return str == nullptr;
        }
        inline bool operator!=(const PooledString& str, nullptr_t) {
            return !(str == nullptr);
        }
        inline bool operator!=(nullptr_t, const PooledString& str) {
            return str != nullptr;
        }

    }
}
