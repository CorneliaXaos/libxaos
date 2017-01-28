#ifndef     LIBXAOS_CORE_TIMING_STOPWATCH_H
#define     LIBXAOS_CORE_TIMING_STOPWATCH_H

#include <array>
#include <chrono>

#include "timing/Clock.h"

namespace libxaos {
    namespace timing {

        class Stopwatch {

            public:

                //! Creates a Stopwatch.  The watch starts ticking the moment
                //! it's created.
                Stopwatch();
                //! Create a Stopwatch that averages the past N frames
                Stopwatch(unsigned short);
                ~Stopwatch();

                Stopwatch(const Stopwatch&);
                Stopwatch& operator=(const Stopwatch&);
                Stopwatch(Stopwatch&&);
                Stopwatch& operator=(Stopwatch&&);

                //! Ticks this Stopwatch.
                void tick();
                //! Restarts this Stopwatch.
                void restart();

                //! Returns the current frame's time
                inline Duration getFrameTime() const;
                //! Returns the average frame time (if it is tracking averages)
                inline Duration getAverageTime() const;

            private:
                //! The array of data points.  Dynamically allocated.
                Duration _frames[];
                //! The count of data points in this Stopwatch.
                unsigned short _frameCount;
        };

    }
}

#endif   // LIBXAOS_CORE_TIMING_STOPWATCH_H
