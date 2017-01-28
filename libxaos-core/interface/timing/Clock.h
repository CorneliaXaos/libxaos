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
            typedef Duration std::chrono::high_resolution_clock::duration;
            //! A wrapper around the high_resolution_clock's time_point type.
            typedef TimePoint std::chrono::high_resolution_clock::time_point;

            //! Obtains the current time.
            inline TimePoint getTime();
        }

    }
}

#endif   // LIBXAOS_CORE_TIMING_CLOCK_H
