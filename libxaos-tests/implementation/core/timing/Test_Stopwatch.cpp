/**
 *  @file Test_Stopwatch.cpp
 *  @brief Tests: libxaos-core:timing/Stopwatch.h
 *
 *  Constructs a stopwatch and runs several tests on values.  Does the best it
 *  can since ensuring time durations are of a particular quantity is not
 *  possible.
 */

#include <chrono>
#include <thread>

#include "timing/Clock.h"
#include "timing/Stopwatch.h"

#include "catch.hpp"

// Define a few types
using Stopwatch = libxaos::timing::Stopwatch;

TEST_CASE("CORE:TIMING/Stopwatch | Can Create Stopwatches", "[core]") {
    // Make some watches! :D
    volatile Stopwatch watch1 {};
    volatile Stopwatch watch2 {5};

    // if this compiles and executes no problems!
}

TEST_CASE("CORE:TIMING/Stopwatch | Can tick and restart watches", "[core]") {
    Stopwatch watch {};
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    watch.tick();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    watch.reset();

    // Again, if this compiles without error and executes no problems!
    // We'll test these results specifically in the following case.
}

TEST_CASE("CORE:TIMING/Stopwatch | Can Check Frame Times", "[core]") {
    Stopwatch watch1 {};
    Stopwatch watch2 {2};
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    watch1.tick();
    watch2.tick();
    Clock::Duration duration1 = watch1.getFrameTime();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    watch2.tick();
    Clock::Duration duration2 = watch2.getAverageTime();
    watch2.reset();
    Clock::Duration duration3 = watch2.getFrameTime();
    Clock::Duration duration4 = watch2.getAverageTime();

    // They should AT LEAST be this accurate.  Preferably a hell of a lot more.
    REQUIRE(duration1 > std::chrono::milliseconds(80));
    REQUIRE(duration2 > std::chrono::milliseconds(80));

    // These should be Zero
    REQUIRE(duration3 == Clock::Duration::zero);
    REQUIRE(duration4 == Clock::Duration::zero);
}
