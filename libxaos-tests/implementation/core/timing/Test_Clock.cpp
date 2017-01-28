/**
 *  @file Test_Clock.cpp
 *  @brief Tests: libxaos-core:timing/Clock.h
 *
 *  Access the minimized Clock API and tests that it functions correctly.
 */

#include <chrono>
#include <thread>

#include "timing/Clock.h"

#include "catch.hpp"

// Use a namespace
using namespace libxaos::timing;

TEST_CASE("CORE:TIMING/Clock | Can Access the Clock", "[core][timing]") {
    // This is hard to test.. will just see that it works.
    Clock::TimePoint time = Clock::getTime();

    REQUIRE(time != Clock::TimePoint::min());
}

TEST_CASE("CORE:TIMING/Clock | Clock Actually Represents Time",
        "[core][timing]") {
    Clock::TimePoint timeStart = Clock::getTime();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    Clock::TimePoint timeEnd = Clock::getTime();
    Clock::Duration duration = timeEnd - timeStart;

    // I highly expect it to be AT LEAST this accurate.
    REQUIRE(duration > std::chrono::milliseconds(80));
}
