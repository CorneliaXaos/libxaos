/**
 *  @file Clock.cpp
 *  @brief Implements: libxaos-core:timing/Clock.h
 *
 *  This file provides implementations for the wrappers in the
 *  libxaos::timing::Clock namespace.
 */

#include <chrono>

#include "timing/Clock.h"

namespace libxaos {
    namespace timing {
        namespace Clock {

            inline TimePoint getTime() {
                return std::chrono::high_resolution_clock::now();
            }

        }
    }
}
