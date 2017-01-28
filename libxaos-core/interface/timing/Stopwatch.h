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
                inline void tick();
                //! Restarts this Stopwatch.
                inline void restart();

                //! Returns the current frame's time
                inline Clock::Duration getFrameTime() const;
                //! Returns the average frame time (if it is tracking averages)
                inline Clock::Duration getAverageTime() const;

            private:
                //! The last time the clock was ticked
                Clock::TimePoint _time;
                //! The array of data points.  Dynamically allocated.
                Clock::Duration* _frames;
                //! The count of data points in this Stopwatch.
                unsigned short _frameCount;
                //! Current data point (Written To)
                unsigned short _frame;
                //! Number of data points written to. (capped to _frameCount)
                unsigned short _framesWritten;
        };

    }
}

// Pull in implementations
#include "timing/Stopwatch-inl.h"

#endif   // LIBXAOS_CORE_TIMING_STOPWATCH_H
