#ifndef     LIBXAOS_CORE_TIMING_STOPWATCH_H
#define     LIBXAOS_CORE_TIMING_STOPWATCH_H

#include <array>
#include <chrono>

#include "timing/Clock.h"

namespace libxaos {
    namespace timing {

        /**
         *  @brief A Stopwatch monitors how much time passses between ticks.
         *
         *  A Stopwatch monitors how much time it takes between consecutive
         *  "ticks".  Note that there is an implicit "tick" when the Stopwatch
         *  is created or restarted.  This "tick" does not store a duration, but
         *  merely serves as the starting value for calculating a duration.
         *
         *  The behavior of this class is modeled after a Stopwatch used by
         *  runners circling a track and measuring their "time between ticks".
         *  As such, it is very convenient to use for measuring the length of
         *  time something repetitive takes.. such as frames in a video game. :)
         */
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
