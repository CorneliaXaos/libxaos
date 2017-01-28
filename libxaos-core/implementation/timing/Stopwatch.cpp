/**
 *  @file Stopwatch.cpp
 *  @brief Implements: libxaos-core:timing/Stopwatch.h
 *
 *  This file provides implementations for the Stopwatch class.
 */

#include <utility>

#include "timing/Clock.h"
#include "timing/Stopwatch.h"

namespace libxaos {
    namespace timing {

        // Constructors
        Stopwatch::Stopwatch() : Stopwatch(1) {}
        Stopwatch::Stopwatch(unsigned short frames) :
                _time(Clock::getTime()), _frames(new Clock::Duration[frames]),
                _frameCount(frames), _frame(frames - 1), _framesWritten(0) {
            tick(); // Creating the Stopwatch starts its ticking.
        }
        Stopwatch::~Stopwatch() {
            //! @todo Replace this with a unique pointer
            if (_frames) delete[] _frames;
        }

        // Copy / Move Semantics
        Stopwatch::Stopwatch(const Stopwatch& other) :
                _time(Clock::getTime()),
                _frames(new Clock::Duration[other._frameCount]),
                _frameCount(other._frameCount), _frame(other._frame),
                _framesWritten(other._framesWritten) {
            for (int i = 0; i < _frameCount; i++) {
                _frames[i] = other._frames[i];
            }
        }
        Stopwatch& Stopwatch::operator=(const Stopwatch& other) {
            if (this != &other) {
                // Copy Time
                _time = other._time;

                // Copy _frames
                if (_frames) delete[] _frames;
                _frames = new Clock::Duration[_frameCount];

                for (int i = 0; i < _frameCount; i++) {
                    _frames[i] = other._frames[i];
                }

                // Copy other data points.
                _frameCount = other._frameCount;
                _frame = other._frame;
                _framesWritten = other._framesWritten;
            }
            return *this;
        }
        Stopwatch::Stopwatch(Stopwatch&& other) :
                _time(other._time), _frames(other._frames),
                _frameCount(other._frameCount), _frame(other._frame),
                _framesWritten(other._framesWritten) {
            other._frames = nullptr;
        }
        Stopwatch& Stopwatch::operator=(Stopwatch&& other) {
            if (this != &other) {
                std::swap(_time, other._time);
                std::swap(_frames, other._frames);
                std::swap(_frameCount, other._frameCount);
                std::swap(_frame, other._frame);
                std::swap(_framesWritten, other._framesWritten);

                // we don't have to delete _frames before we swap
                // since when the RValue is destroyed it will do it
                // for us.
            }
            return *this;
        }
    }
}
