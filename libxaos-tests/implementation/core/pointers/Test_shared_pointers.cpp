/**
 *  @file Test_shared_pointers.cpp
 *  @brief Tests: libxaos-core:pointers/shared_pointers.h
 *
 *  This test operates on and ensures that the StrongPointer and WeakPointer
 *  defined in shared_pointers.h function appropriately.
 */

#include <vector>

#include "pointers/shared_pointers.h"

#include "catch.hpp"

// Define some types
using StrongPointer = libxaos::pointers::StrongPointer<int>;
using WeakPointer = libxaos::pointers::WeakPointer<int>;

TEST_CASE("CORE:POINTERS/shared_pointers | Can Create Shared Pointers",
        "[core]") {
    StrongPointer strong {new int};
    WeakPointer weak = strong.getWeakPointer();

    StrongPointer nullStrong {};
    WeakPointer nullWeak = nullptr;

    REQUIRE(strong);
    REQUIRE(weak);

    REQUIRE(!nullStrong);
    REQUIRE(!nullWeak);

    strong = nullptr;
    // weak should clean itself up upon scope end and free resources
}

TEST_CASE("CORE:POINTERS/shared_pointers | Can access Shared Pointers",
        "[core]") {
    StrongPointer strong1 {new int};
    WeakPointer weak = strong.getWeakPointer();

    *strong = 50;
    StrongPointer strong2 = weak.getStrongPointer();
    REQUIRE(*strong2 == 50);

    strong2 = StrongPointer{new std::vector<int>()};
    strong2->resize(10);
    REQUIRE(strong2->size() == 10);
}

TEST_CASE("CORE:POINTERS/shared_pointers | Null Shared Pointers behave"
        "correctly", "[core]") {
    StrongPointer strong1 {nullptr};
    WeakPointer weak1 = nullptr;

    StrongPointer strong2 = weak1.getStrongPointer();
    WeakPointer weak2 = strong1.getStrongPointer();

    REQUIRE(!strong1);
    REQUIRE(!strong2);
    REQUIRE(!weak1);
    REQUIRE(!weak2);
}

TEST_CASE("CORE:POINTERS/shared_pointers | Can Compare Shared Pointers",
        "[core]") {
    StrongPointer strong1 {new int};
    WeakPointer weak1 = strong1.getWeakPointer();
    StrongPointer strong2 {new int};
    WeakPointer weak2 = strong2.getWeakPointer();
    StrongPointer strong3 = nullptr;
    WeakPointer weak3 = nullptr;
    StrongPointer strong4 = strong2;
    WeakPointer weak4 = weak2;

    // Test equality between Strong and Weak
    REQUIRE(strong1 == weak1);
    REQUIRE(weak1 == strong1);
    // Test inequality between Strong and Weak
    REQUIRE(strong1 != weak2);
    REQUIRE(weak2 != strong1);
    // Test equality to nullptr
    REQUIRE(strong3 == nullptr);
    REQUIRE(weak3 == nullptr);
    // Test inequality to nullptr
    REQUIRE(strong1 != nullptr);
    REQUIRE(weak1 != nullptr);
    // Test equality inside of types
    REQUIRE(strong2 == strong4);
    REQUIRE(weak2 == weak4);
    // Test inequality inside of types
    REQUIRE(strong1 != strong2);
    REQUIRE(weak1 != weak2);
}
