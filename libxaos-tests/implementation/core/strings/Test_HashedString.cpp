/**
 *  @file Test_HashedString.cpp
 *  @brief Tests: libxaos-core:strings/HashedString.h
 *
 *  Tests the HashedString and function (indriectly) for basic functionality.
 *  Given the complexity of testing hash functions, it is assumed that the
 *  implementation is efficient.
 */

#include <string>

#include "memory/store/impl/StaticStore.h"
#include "strings/HashedString.h"
#include "strings/PooledString.h"
#include "strings/StringPool.h"

#include "catch.hpp"

// Define some types
using Store = libxaos::memory::StaticStore<1024, 4, 0>;
using HashedString = libxaos::strings::HashedString;
using PooledString = libxaos::strings::PooledString;
using StringPool = libxaos::strings::StringPool;

TEST_CASE("CORE:STRINGS/HashedString | Can Construct HashedStrings", "[core]") {
    StringPool pool {Store{}};
    PooledString pooledString = pool.process("STRING");
    std::string stdString {"STRING"};

    HashedString hashA {"STRING"};
    HashedString hashB {pooledString};
    HashedString hashC {stdString};

    // We'll also test equality transitivity
    REQUIRE(hashA == hashB);
    REQUIRE(hashB == hashC);
}

TEST_CASE("CORE:STRINGS/HashedString | Can Compare HashedStrings", "[core]") {
    StringPool pool {Store{}};
    PooledString stringA = pool.process("TEST");
    PooledString stringB = nullptr;
    const char* stringC = "TEST";
    const char* stringD = nullptr;
    std::string stringE = "ANOTHER TEST";

    HashedString hashA {stringA};
    HashedString hashB {stringB};
    HashedString hashC {stringC};
    HashedString hashD {stringD};
    HashedString hashE {stringE};
    HashedString hashF {""};

    REQUIRE(hashA == hashC);
    REQUIRE(hashA != hashB);
    REQUIRE(hashB == hashD);
    REQUIRE(hashC != hashE);
    REQUIRE(hashB == HashedString::NULL_STRING);
    REQUIRE(hashF == HashedString::EMPTY_STRING);
}
