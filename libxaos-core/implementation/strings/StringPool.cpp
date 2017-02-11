/**
 *  @file StringPool.cpp
 *  @brief Implements: libxaos-core:strings/StringPool.h
 *
 *  This file provides implementations for the StringPool class.
 */

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <climits>
#include <cstring>
#include <utility>

#include "memory/store/IStore.h"
#include "memory/store/impl/StaticStore.h"
#include "strings/PooledString.h"
#include "strings/StringPool.h"

// Some cpp using statements
using IStore = libxaos::memory::IStore;

namespace libxaos {
    namespace strings {

        // Constructors
        StringPool::StringPool(IStore* store) : _store(store), _count(0U) {}
        StringPool::~StringPool() {
            if (_store)
                delete _store;
        }

        // Move Semantics (no copying pools!
        StringPool::StringPool(StringPool&& other) :
                _store(other._store), _count(other._count) {}
        StringPool& StringPool::operator=(StringPool&& other) {
            if (this != &other) {
                std::swap(_store, other._store);
                _count = other._count;
            }
            return *this;
        }

        // Helpers! OMG I need them...
        // So..  this finds a str in the pool starting at the pointer pointed
        // to by doublePointer.  It checks up to poolSize entries before
        // returning false.  doublePointer points JUST AFTER the end of the
        // last string
        static bool findString(uint8_t** doublePointer, const char* str,
                unsigned int poolSize) {

            if (str == nullptr || strcmp(str, "") == 0) {
                return false;
            }

            // Step through and see if we can find it
            unsigned int index = 0;
            while (index++ < poolSize) {
                // First, pull out string size
                uint16_t size = *reinterpret_cast<uint16_t*>(*doublePointer);

                // Step the doublePointer forward
                *doublePointer += sizeof(uint16_t); // should be 2

                // Just make sure we're using a char*
                char* cmp = reinterpret_cast<char*>(*doublePointer);

                // Let strcmp do its thing
                if (strcmp(str, cmp) == 0) {
                    // we found it! :D
                    return true; // the passed in uint8_t* now points at it
                } else {
                    // we didn't find it..  increment doublePointer and try
                    // again...
                    *doublePointer += size + 1; // string AND null character
                }
            }

            // if we get here we didn't find it
            return false;
        }

        // Process Function - the meat of it all
        PooledString StringPool::process(const char* str) {
            assert(str); // No null strings!
            assert(strlen(str) > 0); // No empty strings!

            if (str == nullptr)
                return PooledString{nullptr};
            if (strlen(str) == 0)
                return PooledString{nullptr};

            // Grab our pointer to our storage and use helper method
            uint8_t* pointer = _store->getRawStorage();
            if (findString(&pointer, str, _count)) {
                // Our find found it!  Return it as a PooledString
                return PooledString{reinterpret_cast<char*>(pointer)};
            } else {
                // We didn't find it..  we'll have to add it..
                size_t rawSize = strlen(str);
                assert(rawSize <= UINT16_MAX); // REMEMBER THE LIMITS!!
                uint16_t size = static_cast<uint16_t>(rawSize);

                // Make sure that the store can actually HOLD the string..
                uintptr_t storeEnd = reinterpret_cast<uintptr_t>(
                        _store->getRawStorage() + _store->SIZE);
                uintptr_t strEnd = reinterpret_cast<uintptr_t>(
                        pointer + size + sizeof(uint16_t) + 1);
                if (storeEnd >= strEnd && _count < UINT_MAX) {
                    // there's space for this string
                    _count++;
                    uint16_t* sizePtr = reinterpret_cast<uint16_t*>(pointer);
                    *sizePtr = size;
                    pointer += sizeof(uint16_t);
                    char* pooledString = reinterpret_cast<char*>(pointer);
                    strcpy(pooledString, str);

                    return PooledString{pooledString};
                } else {
                    // Store too small (likely) or max count reached
                    // Should probably report something in Debug mode...
                    // In a release build, though, we want to return a nullptr
                    return PooledString{nullptr};
                }
            }
        }

        bool StringPool::contains(const char* str) const {
            uint8_t* store = _store->getRawStorage();
            return findString(&store, str, _count);
        }
        bool StringPool::contains(const PooledString& str) const {
            return contains(str.getCharPointer());
        }
    }
}
