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

TEST_CASE("CORE:STRINGS/StringPool | Pool Handles Filling Up Gracefully",
        "[core][!mayfail]") {
    Store* store = new Store();
    StringPool pool {store};

    const char* REALLY_LONG_STRING = "This is a really long string.  "
            "Specifically, it needs to be at least 1024 characters long to fill"
            " up the Pool completely.  As such.. here's a bit of nonsense: "
            "aldjfdljf lsagjlsag jlsdjg lsdjg lajgl jalg jlaj 4oijt04jt90o4hjto"
            " [ijhaiogtjhrhgjtalrjdgoirjhohjlihesoihaoerghroeghghaiorsdjghoirjd"
            "lkhjakfdhodighobnaoijfvlajhroi gjlkda joidhglajrghoihdgldshgladj "
            "ljdl jdlkj lkdjfg lfd glfgj lksjd ldjf lkjfdgl sjfldjgs iorejlgijr"
            "oimofijgvglrsdjgso djglfdjb orjlrjhl sr kjfdlj hlkfsdjobilkjtioblk"
            "bj tb oisjsl bosloibsjisotjsobijroj 8oj oidujbo jsod ujbosj 9ojbo "
            "joi js  s654 646 s4s35 1s65 165 16 4654654 654 654 61 684 684 6 "
            "5168 416 1 684 61 8641 61891 6848 46454 654 684798 746 79 7 65 46 "
            "1 31 321 321 32 1321 321321 321 654 8697 465 4sgkslf jgl;sdjg ldjg"
            " ldjg; sfjg l;jz98gpiogkljg;ljsdljg fljsg lfdjg l;sdjglgfjsfdlk;sj"
            "gdklgjfdl;kgj fdsjh;lfdkjhslkfdjhgfdlkhjslfkdjdhlkfdjhl;jd lfjhs;l"
            " jfsl;h jkjdslkfjaslajg alsdjg lsjdg laj laj ....  And this string"
            " is, now, just about as long as I need it to be...  Just over "
            "1024 characters...  srsly...";
    const char* SMALL_STRING = "THIS IS A TINY STRING.";

    // This SHOULD fail on debug builds because of assert calls.
    PooledString failAdd1 = pool.process(REALLY_LONG_STRING);
    PooledString addedString = pool.process(SMALL_STRING);
    PooledString failAdd2 = pool.process(REALLY_LONG_STRING);

    REQUIRE(failAdd1 == nullptr);
    REQUIRE(addedString != nullptr);
    REQUIRE(failAdd2 == nullptr);
}
