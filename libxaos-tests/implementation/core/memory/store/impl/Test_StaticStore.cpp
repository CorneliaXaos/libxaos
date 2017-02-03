/**
 *  @file Test_StaticStore.cpp
 *  @brief Tests: libxaos-core:memory/store/impl/StaticStore.h
 *
 *  Several StaticStores are constructed in mememory, populated with data,
 *  and tested to see if said data persists.
 */

#include <cstdint>

#include "memory/store/impl/StaticStore.h"

#include "catch.hpp"

// Define some types.
constexpr short Store128_ALIGN = 4;
constexpr short Store256_ALIGN = 64;
constexpr short Store512_ALIGN = 128;
constexpr short Store4096_ALIGN = 4096;  // THIS IS RIDICULOUS

using Store128 = libxaos::memory::StaticStore<128, Store128_ALIGN, 0>;
using Store256 = libxaos::memory::StaticStore<256, Store256_ALIGN, 0>;
using Store512 = libxaos::memory::StaticStore<512, Store512_ALIGN, 0>;
using Store4096 = libxaos::memory::StaticStore<4096, Store4096_ALIGN, 0>;

TEST_CASE("CORE:MEMORY/STORE/IMPL/StaticStore | Stores hold data.",
        "[core][memory]") {

    // create our stores to test
    Store128 storeA {};
    Store256 storeB {};
    Store512 storeC {};

    REQUIRE(storeA.getRawStorage());
    REQUIRE(storeB.getRawStorage());
    REQUIRE(storeC.getRawStorage());

    // loop through and populate stores with data
    for (int i = 0; i < 128 + 256 + 512; i++) {
        uint8_t* data = nullptr;

        if (i < 128) {
            data = storeA.getRawStorage() + i;
        } else if (i < 256) {
            data = storeB.getRawStorage() + (i - 128);
        } else {
            data = storeC.getRawStorage() + (i - 128 - 256);
        }

        *data = i;
    }

    // Verify data is correct.
    uint8_t index = 0;
    for (int i = 0; i < 128 + 256 + 512; i++) {
        INFO("Current iteration: " << i);
        if (i < 128) {
            REQUIRE(*(storeA.getRawStorage() + i) == index);
        } else if (i < 256) {
            REQUIRE(*(storeB.getRawStorage() + i - 128) == index);
        } else {
            REQUIRE(*(storeC.getRawStorage() + i - 128 - 256) == index);
        }

        index++;
    }
}

TEST_CASE("CORE:MEMORY/STORE/IMPL/StaticStore | Stores are aligned.",
        "[core][memory][!mayfail]") {

    // create our stores
    Store128 storeA {};
    Store256 storeB {};
    Store512 storeC {};
    Store4096 storeD {};

    // Test alignments
    uintptr_t addressA = reinterpret_cast<uintptr_t>(storeA.getRawStorage());
    uintptr_t addressB = reinterpret_cast<uintptr_t>(storeB.getRawStorage());
    uintptr_t addressC = reinterpret_cast<uintptr_t>(storeC.getRawStorage());
    uintptr_t addressD = reinterpret_cast<uintptr_t>(storeD.getRawStorage());

    REQUIRE(addressA % Store128_ALIGN == 0);
    REQUIRE(addressB % Store256_ALIGN == 0);
    REQUIRE(addressC % Store512_ALIGN == 0);
    REQUIRE(addressD % Store4096_ALIGN == 0);
}
