/**
 *  @file Clock.cpp
 *  @brief Inline Implements for: libxaos-core:timing/Clock.h
 *
 *  This file provides inline implementations for the wrappers in the
 *  libxaos::timing::Clock namespace.
 */

#include <chrono>

namespace libxaos {
    namespace timing {
        namespace Clock {

            inline TimePoint getTime() {
                return std::chrono::high_resolution_clock::now();
            }

        }
    }
}
