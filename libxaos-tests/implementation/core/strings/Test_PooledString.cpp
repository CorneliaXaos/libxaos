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
    volatile StringPool pool {Store{}};

    // If this compiles and runs.. good for us! :D
}

TEST_CASE("CORE:STRINGS/StringPool | Can Add Strings to Pool", "[core]") {
    StringPool pool {Store{}};
    PooledString nullString = pool.process(nullptr);
    PooledString pooledString = pool.process("I am now pooled.");

    REQUIRE(!pool.contains(nullString)); // Shouldn't exist
    REQUIRE(pool.contains("I am now pooled."));
    REQUIRE(pool.contains(pooledString));
}

TEST_CASE("CORE:STRINGS/PooledString | Can Create Null Strings", "[core]") {
    StringPool pool {Store{}};
    PooledString pooledString = pool.process("Waste.");

    PooledString nullString {nullptr};
    pooledString = nullptr;

    REQUIRE(nullString == nullptr);
    REQUIRE(nullString.getCharPointer() == nullptr);
    REQUIRE(pooledString == nullptr);
    REQUIRE(pooledString.getCharPointer() == nullptr);
}

TEST_CASE("CORE:STRINGS/PooledString | Can Test for Valid Strings", "[core]") {
    StringPool pool {Store{}};
    PooledString stringA = pool.process("I'm valid!");
    PooledString stringB = nullptr; // I'm not! :C

    REQUIRE(stringA);
    REQUIRE(!stringB);
}

TEST_CASE("CORE:STRINGS/PooledString | A PooledString contains the proper"
        " string.", "[core]") {
    StringPool pool {Store{}};
    const char* compare = "I NEED TO BE TESTED!";
    PooledString pooledString = pool.process(compare);

    REQUIRE((strcmp(compare, pooledString.getCharPointer()) == 0));
}

TEST_CASE("CORE:STRINGS/PooledString | Can Compare PooledStrings", "[core]") {
    StringPool pool {Store{}};
    PooledString stringA = pool.process("COMPARE ME!");
    PooledString stringB = pool.process("COMPARE ME!");
    PooledString stringC = pool.process("COMPARE ME TOO!");
    PooledString stringD = pool.process(nullptr);
    PooledString stringE = nullptr;

    REQUIRE(stringA != nullptr);
    REQUIRE(stringA == stringB);
    REQUIRE(stringB != stringC);
    REQUIRE(stringD == nullptr);
    REQUIRE(stringD == stringE);
}
