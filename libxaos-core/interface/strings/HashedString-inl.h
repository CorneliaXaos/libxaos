/**
 *  @file HashedString-inl.h
 *  @brief Inline implements: libxaos-core:strings/HashedString.h
 *
 *  This file provides inline implementations for the HashedString class.
 */

namespace libxaos {
    namespace strings {

        inline bool operator==(const HashedString& a, const HashedString& b) {
            return a.getHash() == b.getHash();
        }
        inline bool operator!=(const HashedString& a, const HashedString& b) {
            return !(a == b);
        }
        inline bool operator==(const HashedString& string, HashType hash) {
            return string.getHash() == hash;
        }
        inline bool operator==(HashType hash, HashedString& string) {
            return string == hash;
        }
        inline bool operator!=(const HashedString& string, HashType hash) {
            return !(string == hash);
        }
        inline bool operator!=(HashType hash, const HashedString& string) {
            return string != hash;
        }

    }
}
