/**
 *  @file Test_StringPool.cpp
 *  @brief Tests: libxaos-core:strings/StringPool.h
 *  @brief Tests: libxaos-core:strings/PooledString.h
 *
 *  Constructs some PooledStrings via a StringPool.  This class tests two
 *  constructs simultaneously given their entanglement and function.
 */

#include <cstring>

#include "memory/store/impl/StaticStore.h"
#include "strings/StringPool.h"
#include "strings/PooledString.h"

#include "catch.hpp"

// Define a few types
using Store = libxaos::memory::StaticStore<1024, 4, 0>;
using StringPool = libxaos::strings::StringPool;
using PooledString = libxaos::strings::PooledString;

TEST_CASE("CORE:STRINGS/StringPool | Can Create StringPools", "[core]") {
    Store* store = new Store();
    volatile StringPool pool {store}; // acquires ownership

    // If this compiles and runs.. good for us! :D
}

TEST_CASE("CORE:STRINGS/StringPool | Can Add Strings to Pool", "[core]") {
    Store* store = new Store();

    StringPool pool {store}; // acquires ownership
    PooledString nullString = nullptr;
    PooledString pooledString = pool.process("I am now pooled.");

    REQUIRE(!pool.contains(nullString)); // Shouldn't exist
    REQUIRE(pool.contains("I am now pooled."));
    REQUIRE(pool.contains(pooledString));
}

TEST_CASE("CORE:STRINGS/PooledString | Can Create Null Strings", "[core]") {
    Store* store = new Store();

    StringPool pool {store}; // acquires ownership
    PooledString pooledString = pool.process("Waste.");

    PooledString nullString {nullptr};
    pooledString = nullptr;

    REQUIRE(nullString == nullptr);
    REQUIRE(nullString.getCharPointer() == nullptr);
    REQUIRE(pooledString == nullptr);
    REQUIRE(pooledString.getCharPointer() == nullptr);
}

TEST_CASE("CORE:STRINGS/PooledString | Can Test for Valid Strings", "[core]") {
    Store* store = new Store();

    StringPool pool {store}; // acquires ownership
    PooledString stringA = pool.process("I'm valid!");
    PooledString stringB = nullptr; // I'm not! :C

    REQUIRE(stringA);
    REQUIRE(!stringB);
}

TEST_CASE("CORE:STRINGS/PooledString | A PooledString contains the proper"
        " string.", "[core]") {
    Store* store = new Store();

    StringPool pool {store}; // acquires ownership
    const char* compare = "I NEED TO BE TESTED!";
    PooledString pooledString = pool.process(compare);

    REQUIRE((strcmp(compare, pooledString.getCharPointer()) == 0));
}

TEST_CASE("CORE:STRINGS/PooledString | Can Compare PooledStrings", "[core]") {
    Store* store = new Store();

    StringPool pool {store}; // acquires ownership
    PooledString stringA = pool.process("COMPARE ME!");
    PooledString stringB = pool.process("COMPARE ME!");
    PooledString stringC = pool.process("COMPARE ME TOO!");
    PooledString stringD = nullptr;

    REQUIRE(stringA != nullptr);
    REQUIRE(stringA == stringB);
    REQUIRE(stringB != stringC);
    REQUIRE(stringD == nullptr);
}
