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
using Store128 = libxaos::memory::StaticStore<128, 4, 0>;
using Store256 = libxaos::memory::StaticStore<256, 4, 1>;
using Store512 = libxaos::memory::StaticStore<512, 4, 2>;

TEST_CASE("CORE:MEMORY/STORE/IMPL/StaticStore", "[core][memory]") {

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
        if (i < 128) {
            REQUIRE(*(storeA.getRawStorage() + index) == index);
        } else if (i < 256) {
            REQUIRE(*(storeB.getRawStorage() + index - 128) == index);
        } else {
            REQUIRE(*(storeC.getRawStorage() + index - 128 - 256) == index);
        }

        index++;
    }
}
