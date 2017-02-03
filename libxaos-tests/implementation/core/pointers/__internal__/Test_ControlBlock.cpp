/**
 *  @file Test_ControlBlock.cpp
 *  @brief Tests: libxaos-core:pointers/__internal__/ControlBlock.cpp
 *
 *  Constructs a ControlBlock and manipulates it testing to ensure that it
 *  behaves as expected.  This is somewhat difficult since ControlBlocks are
 *  supposed to live in Heap memory and have more than one owner.
 */

#include "pointers/__internal__/ControlBlock.h"

#include "catch.hpp"

// Use a namespace
using namespace libxaos::pointers::internal;

TEST_CASE("CORE:POINTERS/INTERNAL/ControlBlock | Can Create ControlBlocks",
        "[core]") {

    // New some memory
    int* intPointer = new int;
    int* intArrayPointer = new int[5];

    // Construct our blocks
    auto blockA = ControlBlock<int, PointerType::PLAIN>::create(intPointer);
    auto blockB = ControlBlock<int, PointerType::ARRAY>
            ::create(intArrayPointer);

    REQUIRE(blockA->getPointer() == intPointer);
    REQUIRE(blockB->getPointer() == intArrayPointer);

    // Cleanup
    delete blockA;
    delete blockB;
}

TEST_CASE("CORE:POINTERS/INTERNAL/ControlBlock | ControlBlocks delete Pointers",
        "[core]") {

    // New some memory
    int* intPointer = new int;
    int* intArrayPointer = new int[5];

    // Construct our blocks
    auto blockA = ControlBlock<int, PointerType::PLAIN>::create(intPointer);
    auto blockB = ControlBlock<int, PointerType::ARRAY>
            ::create(intArrayPointer);

    // Simulate adding owners
    blockA->incrementReference(ReferenceType::STRONG);
    blockA->incrementReference(ReferenceType::WEAK);
    blockB->incrementReference(ReferenceType::STRONG);
    blockB->incrementReference(ReferenceType::WEAK);

    // Remove strong references
    blockA->decrementReference(ReferenceType::STRONG);
    blockB->decrementReference(ReferenceType::STRONG);

    // Verify
    REQUIRE(blockA->getPointer() == nullptr);
    REQUIRE(blockB->getPointer() == nullptr);

    // This should cleanup nicely:
    blockA->decrementReference(ReferenceType::WEAK);
    blockB->decrementReference(ReferenceType::WEAK);
}

TEST_CASE("CORE:POINTERS/INTERNAL/ControlBlock | ControlBlocks reflect "
        "internal pointer status", "[core]") {

    // New some memory
    int* intPointer = new int;
    int* intArrayPointer = new int[5];

    // Construct our blocks
    auto blockA = ControlBlock<int, PointerType::PLAIN>::create(intPointer);
    auto blockB = ControlBlock<int, PointerType::ARRAY>
            ::create(intArrayPointer);

    // Simulate adding owners
    blockA->incrementReference(ReferenceType::STRONG);
    blockA->incrementReference(ReferenceType::WEAK);
    blockB->incrementReference(ReferenceType::STRONG);
    blockB->incrementReference(ReferenceType::WEAK);

    // Verify bool operators
    REQUIRE(*blockA);
    REQUIRE(*blockB);

    // Remove strong references
    blockA->decrementReference(ReferenceType::STRONG);
    blockB->decrementReference(ReferenceType::STRONG);

    // Verify again
    REQUIRE(!*blockA);
    REQUIRE(!*blockB);

    // This should cleanup nicely:
    blockA->decrementReference(ReferenceType::WEAK);
    blockB->decrementReference(ReferenceType::WEAK);
}
