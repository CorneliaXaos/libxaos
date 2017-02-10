/**
 *  @file HashedString.cpp
 *  @brief Implements: libxaos-core:strings/HashedString.h
 *
 *  This file provides implementations for the HashedString class.
 */

#include <cstdint>
#include <cstring>

#include "strings/HashedString.h"
#include "strings/PooledString.h"

namespace libxaos {
    namespace strings {

        // Unfortunately, this requires knowing the implementation from
        // the header file.  I could set up a preprocessor define or constexpr,
        // but I don't want these values in teh public header because I don't
        // wan't people to feel it's okay to assign them manually.. use the
        // constants in the class!
        HashedString::NULL_STRING {UINT32_MAX};
        HashedString::EMPTY_STRING {0};

        // Our hashing algorithm.  Only visible here.
        // Algorithm is 'djb2'; Source: http://www.cse.yorku.ca/~oz/hash.html
        // Some slight modifications:
        // Manually assign to specific values for nullptr and empty string
        // Shift end values slightly if hash overlaps with manually assigned
        // values for NULL_STRING and EMPTY_STRING
        HashedString::HashType hashString(const char* str) {
            if (str == nullptr)
                return HashedString::NULL_STRING;
            else if (strlen(str) == 0)
                return HashedString::EMPTY_STRING;

            const unsigned char* hashPtr =
                    reinterpret_cast<const unsigned char*>(str);

            HashedString::HashType hash = 5381;

            int c;
            while (c = *str++)
                hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

            // Shift our hash slightly if needed
            if (hash == HashedString::NULL_STRING)
                hash--;
            else if (hash == HashedString::EMPTY_STRING)
                hash++;

            return hash;
        }

        // Constructors
        HashedString::HashedString(const char* str) : _hash(hashString(str)) {}
        HashedString::HashedString(std::string str) : HashedString(str.c_str) {}
        HashedString::HashedString(const PooledString& str) :
                HashedString(str.getCharPointer()) {}
        HashedString::~HashedString() {};

        // Copy / Move Semantics
        HashedString::HashedString(const HashedString& other) :
                _hash(other._hash) {}
        HashedString& HashedString::operator=(const HashedString& other) {
            _hash = other._hash;
            return *this;
        }
        HashedString::HashedString(HashedString&& other) :
                _hash(other._hash) {}
        HashedString& HashedString::operator=(HashedString&& other) {
            _hash = other._hash;
            return *this;
        }
    }
 }
