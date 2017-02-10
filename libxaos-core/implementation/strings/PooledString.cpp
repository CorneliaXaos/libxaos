/**
 *  @file PooledString.cpp
 *  @brief Implements: libxaos-core:strings/PooledString.h
 *
 *  This file provides implementations for the PooledString class.
 */

#include <cstddef>

#include "strings/PooledString.h"

namespace libxaos {
    namespace strings {

        // Public Constructors
        PooledString::PooledString(nullptr_t) : _string(nullptr) {}
        PooledString::~PooledString() {}

        // Copy / Move Semantics
        PooledString::PooledString(const PooledString& other) :
                _string(other._string) {}
        PooledString& PooledString::operator=(const PooledString& other) {
            _string = other._string;
            return *this;
        }
        PooledString::PooledString(PooledString&& other) :
                _string(other._string) {}
        PooledString& PooledString::operator=(PooledString&& other) {
            _string = other._string;
            return *this;
        }

        // nullptr Assignment
        PooledString& PooledString::operator=(nullptr_t) {
            _string = nullptr;
            return *this;
        }

        // Private Constructor
        PooledString::PooledString(char* str) : _string(str) {}
    }
}
