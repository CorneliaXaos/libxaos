/**
 *  @file Stopwatch-inl.h
 *  @brief Inline Implements for: libxaos-core:timing/Stopwatch.h
 *
 *  This file provides inlined implementations for the Stopwatch class.
 */

#include "timing/Clock.h"

namespace libxaos {
    namespace timing {

        // Ticking Operations
        inline void Stopwatch::tick() {
            _frame = (_frame + 1) % _frameCount;
            Clock::TimePoint time = Clock::getTime();
            _frames[i] = time - _time;
            _time = time;

            if (_framesWritten < _frameCount)
                _framesWritten++;
        }
        inline void Stopwatch::restart() {
            // Reset Frames
            for (int i = 0; i < _frameCount; i++) {
                _frames[i] = Clock::Duration::zero;
            }

            // Reset Tracking Points
            _frame = _frameCount - 1;
            _framesWritten = 0;

            // Reset our initial time.
            _time = Clock::getTime();
        }

        // Evaluation Operations
        inline Clock::Duration getFrameTime() const {
            return _frames[_frame];
        }
        inline Clock::Duration getAverageTime() const {
            Clock::Duration sum = Clock::Duration::zero;
            for (int i = 0; i < _framesWritten; i++) {
                sum += _frames[i];
            }
            return sum / _framesWritten;
        }
    }
}
