/**
 *  @file Test_Vector.cpp
 *  @brief Tests: libxaos-maths:Vector.h
 *
 *  Constructs several Vectors and tests the implementation of all operations.
 */
#include <cmath>

#include "Vector.h"

#include "catch.hpp"

// Define a few types
using IntVector1 = libxaos::maths::Vector<int, 1>;
using IntVector2 = libxaos::maths::Vector<int, 2>;
using IntVector3 = libxaos::maths::Vector<int, 3>;
using IntVector4 = libxaos::maths::Vector<int, 4>;
using FloatVector3 = libxaos::maths::Vector<float, 3>;

TEST_CASE("MATHS:Vector | Can Create Vectors", "[maths]") {
    // Default initialize several Vectors
    volatile IntVector1 vec1 {};
    volatile IntVector2 vec2 {};
    volatile IntVector3 vec3 {};
    volatile IntVector4 vec4 {};
    volatile FloatVector3 vec5 {};

    // Initialize a Vector using an initializer list
    IntVector3 vec6 {3, 4, 5};
    REQUIRE(vec6[0] == 3);
    REQUIRE(vec6[1] == 4);
    REQUIRE(vec6[2] == 5);
}

TEST_CASE("MATHS:Vector | Can Access Vector Data", "[maths]") {
    IntVector4 vec {3, 5, 7, 9};

    REQUIRE(vec.x() == 3);
    REQUIRE(vec.y() == 5);
    REQUIRE(vec.z() == 7);
    REQUIRE(vec[3]  == 9);
    REQUIRE(vec.at(3) == 9);
}

TEST_CASE("MATHS:Vector | Can Set Vector Data", "[maths]") {
    IntVector4 vec {};
    vec.x(3);
    vec.y(5);
    vec[2] = 7;
    vec.at(3) = 9;

    REQUIRE(vec.x() == 3);
    REQUIRE(vec.y() == 5);
    REQUIRE(vec.z() == 7);
    REQUIRE(vec[3]  == 9);
}

TEST_CASE("MATHS:Vector | Vector (In)Equality", "[maths]") {
    IntVector3 vec1 {1, 3, 5};
    IntVector3 vec2 {2, 4, 6};
    IntVector3 vec3 {1, 3, 5};

    REQUIRE(vec1 == vec3);
    REQUIRE(vec1 != vec2);
}

TEST_CASE("MATHS:Vector | Vector Negation", "[maths]") {
    IntVector3 vec {1, 3, 5};
    IntVector3 neg = -vec;

    REQUIRE((neg == IntVector3{-1, -3, -5}));
}

TEST_CASE("MATHS:Vector | Vector Scaling (Multiplication)", "[maths]") {
    IntVector3 vec {1, 3, 5};
    IntVector3 scale1 = vec * 2;
    IntVector3 scale2 = 3 * vec;
    vec *= 4;

    REQUIRE((vec == IntVector3{4, 12, 20}));
    REQUIRE((scale1 == IntVector3{2, 6, 10}));
    REQUIRE((scale2 == IntVector3{3, 9, 15}));
}

TEST_CASE("MATHS:Vector | Vector Scaling (Division)", "[maths]") {
    IntVector3 vec {6, 18, 30};
    IntVector3 scale = vec / 2;
    vec /= 3;

    REQUIRE((scale == IntVector3{3, 9, 15}));
    REQUIRE((vec == IntVector3{2, 6, 10}));
}

TEST_CASE("MATHS:Vector | Vector Addition", "[maths]") {
    IntVector3 vec1 {1, 3, 5};
    IntVector3 vec2 {2, 4, 6};
    IntVector3 vec3 {3, 5, 7};
    IntVector3 vec4 = vec1 + vec2;
    vec3 += vec2;
    IntVector3 vec5 = vec1 + 5;
    IntVector3 vec6 = 5 + vec2;

    REQUIRE((vec4 == IntVector3{3, 7, 11}));
    REQUIRE((vec3 == IntVector3{5, 9, 13}));
    REQUIRE((vec5 == IntVector3{6, 8, 10}));
    REQUIRE((vec6 == IntVector3{7, 9, 11}));
}

TEST_CASE("MATHS:Vector | Vector Subtraction", "[maths]") {
    IntVector3 vec1 {1, 3, 5};
    IntVector3 vec2 {2, 4, 6};
    IntVector3 vec3 {3, 5, 7};
    IntVector3 vec4 = vec1 - vec2;
    vec3 -= vec2;
    IntVector3 vec5 = vec2 - 7;

    REQUIRE((vec4 == IntVector3{-1, -1, -1}));
    REQUIRE((vec3 == IntVector3{1, 1, 1}));
    REQUIRE((vec5 == IntVector3{-5, -3, -1}));
}

TEST_CASE("MATHS:Vector | Vector Magnitudes", "[maths]") {
    IntVector2 vec1 {3, 4};
    IntVector2 vec2 {5, 6};
    FloatVector3 vec3 {1.5F, 2.5F, 3.5F};

    REQUIRE(magnitude(vec1) == 5);
    REQUIRE(magnitude2(vec2) == 61);
    REQUIRE(fabs(magnitude(vec3) -
            sqrt(1.5F * 1.5F + 2.5F * 2.5F + 3.5F * 3.5F)) < 0.001F);
}

TEST_CASE("MATHS:Vector | Dot Product", "[maths]") {
    IntVector4 vec1 {1, 2, 3, 4};
    IntVector4 vec2 {5, 6, 7, 8};

    REQUIRE((dot(vec1, vec2) == 70));
}

TEST_CASE("MATHS:Vector | Cross Product", "[maths]") {
    IntVector3 vec1 {1, 3, 5};
    IntVector3 vec2 {2, 4, 6};
    IntVector3 vec3 = cross(vec1, vec2);

    REQUIRE((vec3 == IntVector3{-2, 4, -2}));
}
