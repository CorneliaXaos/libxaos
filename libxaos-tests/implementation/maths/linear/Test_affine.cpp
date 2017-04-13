/**
 *  @file Test_affine.cpp
 *  @brief Tests: libxaos-maths:affine.h
 *
 *  Tests the affine transform creation functions in the affine namespace.
 */

#include <cmath>

#include "linear/affine.h"
#include "linear/Matrix.h"
#include "linear/Vector.h"

#include "catch.hpp"

// Define a few types
using FloatVector2 = libxaos::linear::Vector<float, 2>;
using FloatVector3 = libxaos::linear::Vector<float, 3>;
using FloatVector4 = libxaos::linear::Vector<float, 4>;

using FloatMatrix3 = libxaos::linear::Matrix<float, 3, 3>;
using FloatMatrix4 = libxaos::linear::Matrix<float, 4, 4>;

// And bring in the namespace.. because that's a lot of typing...
using namespace libxaos::linear::affine;

// And finally a constant expression:
constexpr double PI() {return std::acos(-1);}

TEST_CASE("MATHS:affine | 2D Scaling", "[maths]") {
    FloatVector3 vec {1, 5, 1}; // homogenous
    FloatMatrix3 scale1 = get2DScaling(2.0F, 2.0F);
    FloatMatrix3 scale2 = get2DScaling(FloatVector2{3, 5});

    auto result1 = scale1 * vec;
    auto result2 = scale2 * vec;

    // I really should define some floating point compares for these...
    // I'll put it on the TODO list...
    //! @todo define floating point compares... :P
    REQUIRE((result1.x() -  2 < 0.001F));
    REQUIRE((result1.y() - 10 < 0.001F));
    REQUIRE((result2.x() -  3 < 0.001F));
    REQUIRE((result2.y() - 25 < 0.001F));
}

TEST_CASE("MATHS:affine | 3D Scaling", "[maths]") {
    FloatVector4 vec {1, 5, 10, 1}; // homogenous
    FloatMatrix4 scale1 = get3DScaling(2.0F, 2.0F, 2.0F);
    FloatMatrix4 scale2 = get3DScaling(FloatVector3{3.0F, 5.0F, 7.0F});

    auto result1 = scale1 * vec;
    auto result2 = scale2 * vec;

    REQUIRE((result1.x() -  2 < 0.001F));
    REQUIRE((result1.y() - 10 < 0.001F));
    REQUIRE((result1.z() - 20 < 0.001F));
    REQUIRE((result2.x() -  3 < 0.001F));
    REQUIRE((result2.y() - 25 < 0.001F));
    REQUIRE((result2.z() - 70 < 0.001F));
}

TEST_CASE("MATHS:affine | 2D Rotation Simple", "[maths]") {
    FloatVector3 vec1 {1, 0, 1};
    FloatVector3 vec2 {0, 1, 1};
    FloatMatrix3 rot1 = get2DRotation(static_cast<float>(PI() / 2.0));
    FloatMatrix3 rot2 = get2DRotation(static_cast<float>(-PI()));

    auto result1 = rot1 * vec1;
    auto result2 = rot2 * vec2;

    // result1 should be {0, 1, 1}
    REQUIRE((result1.x() -  0 < 0.001F));
    REQUIRE((result1.y() -  1 < 0.001F));
    REQUIRE((result1.z() -  1 < 0.001F));
    // result2 should be {0, -1, 1}
    REQUIRE((result2.x() -  0 < 0.001F));
    REQUIRE((result2.y() - -1 < 0.001F));
    REQUIRE((result2.z() -  1 < 0.001F));
}

TEST_CASE("MATHS:affine | 2D Rotation Onto", "[maths]") {
    FloatVector3 vec {1, 0, 1};
    FloatVector2 source {1, 0};
    FloatVector2 target {-1, -1};
    normalize(target);
    FloatMatrix3 rot = get2DRotationOnto(source, target);

    auto result = rot * vec;

    // result should be {target, 1}.
    REQUIRE((result.x() - target.x() < 0.001F));
    REQUIRE((result.y() - target.y() < 0.001F));
    REQUIRE((result.z() -          1 < 0.001F));
}

TEST_CASE("MATHS:affine | 3D Rotation Simple", "[maths]") {
    FloatVector4 vec1 {1, 0, 0, 1};
    FloatVector4 vec2 {0, 1, 0, 1};
    FloatVector4 vec3 {0, 0, 1, 1};

    float ninety = static_cast<float>(PI() / 2);
    FloatMatrix4 rot1 = get3DRotation(0.0F, 0.0F, ninety);
    FloatMatrix4 rot2 = get3DRotation(FloatVector3{ninety, 0.0F, 0.0F});
    FloatMatrix4 rot3 = get3DRotation(0.0F, ninety, 0.0F);

    auto result1 = rot1 * vec1;
    auto result2 = rot2 * vec2;
    auto result3 = rot3 * vec3;

    // result1 should be {0, 1, 0, 1}
    REQUIRE((result1.x() - 0 < 0.001F));
    REQUIRE((result1.y() - 1 < 0.001F));
    REQUIRE((result1.z() - 0 < 0.001F));
    REQUIRE((result1[3]  - 1 < 0.001F));
    // result2 should be {0, 0, 1, 1}
    REQUIRE((result2.x() - 0 < 0.001F));
    REQUIRE((result2.y() - 0 < 0.001F));
    REQUIRE((result2.z() - 1 < 0.001F));
    REQUIRE((result2[3]  - 1 < 0.001F));
    // result3 should be {1, 0, 0, 1}
    REQUIRE((result3.x() - 1 < 0.001F));
    REQUIRE((result3.y() - 0 < 0.001F));
    REQUIRE((result3.z() - 0 < 0.001F));
    REQUIRE((result3[3]  - 1 < 0.001F));
}

TEST_CASE("MATHS:affine | 3D Rotation Onto", "[maths]") {
    FloatVector4 vec {1, 0, 0, 1};
    FloatVector3 source {1, 0, 0};
    FloatVector3 target {1, 2, 3};
    normalize(target);
    FloatMatrix4 rot = get3DRotationOnto(source, target);

    auto result = rot * vec;

    // result should be target
    REQUIRE((result.x() - target.x() < 0.001F));
    REQUIRE((result.y() - target.y() < 0.001F));
    REQUIRE((result.z() - target.z() < 0.001F));
    REQUIRE((result[3]  -          1 < 0.001F));
}

TEST_CASE("MATHS:affine | 3D Rotation Arbitrary", "[maths]") {
    FloatVector4 vec {1, 0, 0, 1};
    FloatVector3 axis {0, 0, 1};
    FloatMatrix4 rot = get3DRotationArbitrary(static_cast<float>(PI() / 2.0),
            axis);

    auto result = rot * vec;

    // result should be {0, 1, 0, 1}
    REQUIRE((result.x() - 0 < 0.001F));
    REQUIRE((result.y() - 1 < 0.001F));
    REQUIRE((result.z() - 0 < 0.001F));
    REQUIRE((result[3]  - 1 < 0.001F));
}

TEST_CASE("MATHS:affine | 2D Translation", "[maths]") {
    FloatVector3 vec1 {0, 0, 1};
    FloatVector3 vec2 {1, 1, 1};
    FloatMatrix3 trans1 = get2DTranslation(5.0F, -5.0F);
    FloatMatrix3 trans2 = get2DTranslation(FloatVector2{-1, -1});

    auto result1 = trans1 * vec1;
    auto result2 = trans2 * vec2;

    // result1 should be {5, -5, 1}
    REQUIRE((result1.x() -  5 < 0.001F));
    REQUIRE((result1.y() - -5 < 0.001F));
    REQUIRE((result1.z() -  1 < 0.001F));
    // result2 should be {0, 0, 1}
    REQUIRE((result2.x() -  0 < 0.001F));
    REQUIRE((result2.y() -  0 < 0.001F));
    REQUIRE((result2.z() -  1 < 0.001F));

}

TEST_CASE("MATHS:affine | 3D Translation", "[maths]") {
    FloatVector4 vec1 {0, 0, 0, 1};
    FloatVector4 vec2 {1, 1, 1, 1};
    FloatMatrix4 trans1 = get3DTranslation(5.0F, -5.0F, 5.0F);
    FloatMatrix4 trans2 = get3DTranslation(FloatVector3{-1, -1, -1});

    auto result1 = trans1 * vec1;
    auto result2 = trans2 * vec2;

    // result1 should be {5, -5, 1}
    REQUIRE((result1.x() -  5 < 0.001F));
    REQUIRE((result1.y() - -5 < 0.001F));
    REQUIRE((result1.z() -  5 < 0.001F));
    REQUIRE((result1[3]  -  1 < 0.001F));
    // result2 should be {0, 0, 1}
    REQUIRE((result2.x() -  0 < 0.001F));
    REQUIRE((result2.y() -  0 < 0.001F));
    REQUIRE((result2.z() -  0 < 0.001F));
    REQUIRE((result2[3]  -  1 < 0.001F));
}
