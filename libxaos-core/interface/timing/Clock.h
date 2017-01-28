#ifndef     LIBXAOS_CORE_TIMING_CLOCK_H
#define     LIBXAOS_CORE_TIMING_CLOCK_H

#include <chrono>

namespace libxaos {
    namespace timing {

        /**
         *  @brief Wraps the std::chrono::high_resolution_clock to make it
         *      easier to use.
         *
         *  This namespace wraps the STL implementation of a
         *  high_resolution_clock on a particular system.
         *
         *  Additionally, it wraps the accesses to the clock itself.
         */
        namespace Clock {

            //! A wrapper around the high_resolution_clock's duration type.
            typedef std::chrono::high_resolution_clock::duration Duration;
            //! A wrapper around the high_resolution_clock's time_point type.
            typedef std::chrono::high_resolution_clock::time_point TimePoint;

            //! Obtains the current time.
            inline TimePoint getTime();
        }

    }
}

// Pull in implementations
#include "timing/Clock-inl.h"

#endif   // LIBXAOS_CORE_TIMING_CLOCK_H
