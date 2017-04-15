/**
 *  @file Test_SSEType.cpp
 *  @brief Tests: libxaos-maths:sse/SSEType.h
 *
 *  Constructs several SSEType objects (if possible) and tests the
 *  implementation of all operations.
 */

#include "sse/SSEType.h"
#include "utility/cpu.h"

#include "catch.hpp"

// Only run these tests if we are one of the correct platforms.
#if defined(LIBXAOS_FLAG_CPU_INTEL) || true

// Define a few types
using SSEChar = libxaos::sse::SSEType<char>;
using SSEInt = libxaos::sse::SSEType<int>;
using SSELong = libxaos::sse::SSEType<long long int>;
using SSEFloat = libxaos::sse::SSEType<float>;
using SSEDouble = libxaos::sse::SSEType<double>;

TEST_CASE("MATHS:SSE/SSEType | Can Create Types", "[maths]") {
    SSEChar sseChar {};
    SSEInt sseInt {1};
    SSELong sseLong {45, 8675309};
    volatile SSEFloat sseFloat {};

    // Test that data is populated correctly
    REQUIRE(sseChar[0] == 0);
    REQUIRE(sseInt[0] == 1);
    REQUIRE((sseLong[0] == 45 && sseLong[1] == 8675309));
}

TEST_CASE("MATHS:SSE/SSEType | Can Access Data", "[maths]") {
    SSEInt sse {1, 2, 3, 999};

    REQUIRE(sse[0] == 1);
    REQUIRE(sse[1] == 2);
    REQUIRE(sse.at(2) == 3);
    REQUIRE(sse.at(3) == 999);
}

TEST_CASE("MATHS:SSE/SSEType | Can Set Data", "[maths]") {
    SSEInt sseA {};
    sseA[0] = 1;
    sseA[1] = 2;
    sseA[2] = 3;
    sseA[3] = 999;
    SSEInt sseB {1, 2, 3, 999};

    REQUIRE(sseA == sseB);
}

TEST_CASE("MATHS:SSE/SSEType | Can Compare Data", "[maths]") {
    SSEInt sseIntA {1, 2, 3, 999};
    SSEInt sseIntB {1, 2, 3, 999};
    SSEInt sseIntC {1, 2, 3, 4};
    REQUIRE(sseIntA == sseIntB);
    REQUIRE(sseIntA != sseIntC);

    SSEFloat sseFloatA {1.0F, 2.0F, 3.0F, 999.0F};
    SSEFloat sseFloatB {1.0F, 2.0F, 3.0F, 999.0F};
    SSEFloat sseFloatC {1.0F, 2.0F, 3.0F, 4.0F};
    REQUIRE(sseFloatA == sseFloatB);
    REQUIRE(sseFloatA != sseFloatC);

    SSEDouble sseDoubleA {1.0, 2.0};
    SSEDouble sseDoubleB {1.0, 2.0};
    SSEDouble sseDoubleC {1.0, 4.0};
    REQUIRE(sseDoubleA == sseDoubleB);
    REQUIRE(sseDoubleA != sseDoubleC);
}

TEST_CASE("MATHS:SSE/SSEType | Can Negate Data", "[maths]") {
    SSEInt sseIntA {1, -2, 3, -4};
    SSEInt sseIntB {-1, 2, -3, 4};
    SSEInt negInt = -sseIntA;
    REQUIRE(sseIntB == negInt);

    SSEFloat sseFloatA {1.0F, -2.0F, 3.0F, -4.0F};
    SSEFloat sseFloatB {-1.0F, 2.0F, -3.0F, 4.0F};
    SSEFloat negFloat = -sseFloatA;
    REQUIRE(sseFloatB == negFloat);

    SSEDouble sseDoubleA {1.0, -2.0};
    SSEDouble sseDoubleB {-1.0, 2.0};
    SSEDouble negDouble = -sseDoubleA;
    REQUIRE(sseDoubleB == negDouble);
}

TEST_CASE("MATHS:SSE/SSEType | Can Add Data", "[maths]") {
    SSEInt sseIntA {1, 2, 3, 4};
    SSEInt sseIntB {4, 3, 2, 1};
    SSEInt sseIntC {5, 5, 5, 5};
    SSEInt sumInt = sseIntA + sseIntB;
    sseIntB += sseIntA;
    REQUIRE(sseIntC == sumInt);
    REQUIRE(sseIntC == sseIntB);

    SSEFloat sseFloatA {1.0F, 2.0F, 3.0F, 4.0F};
    SSEFloat sseFloatB {4.0F, 3.0F, 2.0F, 1.0F};
    SSEFloat sseFloatC {5.0F, 5.0F, 5.0F, 5.0F};
    SSEFloat sumFloat = sseFloatA + sseFloatB;
    sseFloatB += sseFloatA;
    REQUIRE(sseFloatC == sumFloat);
    REQUIRE(sseFloatC == sseFloatB);

    SSEDouble sseDoubleA {1.0, 2.0};
    SSEDouble sseDoubleB {4.0, 3.0};
    SSEDouble sseDoubleC {5.0, 5.0};
    SSEDouble sumDouble = sseDoubleA + sseDoubleB;
    sseDoubleB += sseDoubleA;
    REQUIRE(sseDoubleC == sumDouble);
    REQUIRE(sseDoubleC == sseDoubleB);
}

TEST_CASE("MATHS:SSE/SSEType | Can Subtract Data", "[maths]") {
    SSEInt sseIntA {1, 2, 3, 4};
    SSEInt sseIntB {1, 1, 1, 1};
    SSEInt sseIntC {0, 1, 2, 3};
    SSEInt differenceInt = sseIntA - sseIntB;
    sseIntA -= sseIntB;
    REQUIRE(sseIntC == differenceInt);
    REQUIRE(sseIntC == sseIntA);

    SSEFloat sseFloatA {1.0F, 2.0F, 3.0F, 4.0F};
    SSEFloat sseFloatB {1.0F, 1.0F, 1.0F, 1.0F};
    SSEFloat sseFloatC {0.0F, 1.0F, 2.0F, 3.0F};
    SSEFloat differenceFloat = sseFloatA - sseFloatB;
    sseFloatA -= sseFloatB;
    REQUIRE(sseFloatC == differenceFloat);
    REQUIRE(sseFloatC == sseFloatA);

    SSEDouble sseDoubleA {1.0, 2.0};
    SSEDouble sseDoubleB {1.0, 1.0};
    SSEDouble sseDoubleC {0.0, 1.0};
    SSEDouble differenceDouble = sseDoubleA - sseDoubleB;
    sseDoubleA -= sseDoubleB;
    REQUIRE(sseDoubleC == differenceDouble);
    REQUIRE(sseDoubleC == sseDoubleA);
}

TEST_CASE("MATHS:SSE/SSEType | Can Multiply Data", "[maths]") {
    SSEInt sseIntA {1, 2, 3, 4};
    SSEInt sseIntB {2, 2, 2, 2};
    SSEInt sseIntC {2, 4, 6, 8};
    SSEInt productInt = sseIntA * sseIntB;
    sseIntA *= sseIntB;
    REQUIRE(sseIntC == productInt);
    REQUIRE(sseIntC == sseIntA);

    SSEFloat sseFloatA {1.0F, 2.0F, 3.0F, 4.0F};
    SSEFloat sseFloatB {2.0F, 2.0F, 2.0F, 2.0F};
    SSEFloat sseFloatC {2.0F, 4.0F, 6.0F, 8.0F};
    SSEFloat productFloat = sseFloatA * sseFloatB;
    sseFloatA *= sseFloatB;
    REQUIRE(sseFloatC == productFloat);
    REQUIRE(sseFloatC == sseFloatA);

    SSEDouble sseDoubleA {1.0, 2.0};
    SSEDouble sseDoubleB {2.0, 2.0};
    SSEDouble sseDoubleC {2.0, 4.0};
    SSEDouble productDouble = sseDoubleA * sseDoubleB;
    sseDoubleA *= sseDoubleB;
    REQUIRE(sseDoubleC == productDouble);
    REQUIRE(sseDoubleC == sseDoubleA);
}

TEST_CASE("MATHS:SSE/SSEType | Can Divide Data", "[maths]") {
    SSEInt sseIntA {2, 4, 6, 8};
    SSEInt sseIntB {2, 2, 2, 2};
    SSEInt sseIntC {1, 2, 3, 4};
    SSEInt quotientInt = sseIntA / sseIntB;
    sseIntA /= sseIntB;
    REQUIRE(sseIntC == quotientInt);
    REQUIRE(sseIntC == sseIntA);

    SSEFloat sseFloatA {2.0F, 4.0F, 6.0F, 8.0F};
    SSEFloat sseFloatB {2.0F, 2.0F, 2.0F, 2.0F};
    SSEFloat sseFloatC {1.0F, 2.0F, 3.0F, 4.0F};
    SSEFloat quotientFloat = sseFloatA / sseFloatB;
    sseFloatA /= sseFloatB;
    REQUIRE(sseFloatC == quotientFloat);
    REQUIRE(sseFloatC == sseFloatA);

    SSEDouble sseDoubleA {2.0, 4.0};
    SSEDouble sseDoubleB {2.0, 2.0};
    SSEDouble sseDoubleC {1.0, 2.0};
    SSEDouble quotientDouble = sseDoubleA / sseDoubleB;
    sseDoubleA /= sseDoubleB;
    REQUIRE(sseDoubleC == quotientDouble);
    REQUIRE(sseDoubleC == sseDoubleA);
}

TEST_CASE("MATHS:SSE/SSEType | Can Dot Product", "[maths]") {
    SSEInt sseIntA {1, 2, 3, 4};
    SSEInt sseIntB {1, 2, 3, 4};
    int compareInt = 1 + 4 + 9 + 16;
    int resultInt = dot(sseIntA, sseIntB);
    REQUIRE(compareInt == resultInt);

    SSEFloat sseFloatA {1.0F, 2.0F, 3.0F, 4.0F};
    SSEFloat sseFloatB {1.0F, 2.0F, 3.0F, 4.0F};
    float compareFloat = 1.0F + 4.0F + 9.0F + 16.0F;
    float resultFloat = dot(sseFloatA, sseFloatB);
    REQUIRE((!(compareFloat < resultFloat || compareFloat > resultFloat)));

    SSEDouble sseDoubleA {1.0, 2.0};
    SSEDouble sseDoubleB {1.0, 2.0};
    double compareDouble = 1.0 + 4.0;
    double resultDouble = dot(sseDoubleA, sseDoubleB);
    REQUIRE((!(compareDouble < resultDouble || compareDouble > resultDouble)));
}

#endif
