/**
 *  @file Test_Matrix.cpp
 *  @brief Tests: libxaos-maths:linear/Matrix.h
 *
 *  Constructs several Matrices and tests the implementation of all operations.
 */

#include <exception>

#include "linear/Matrix.h"
#include "linear/Vector.h"

#include "catch.hpp"

// Define a few types
using IntMatrix2 = libxaos::linear::Matrix<int, 2, 2>;
using IntMatrix3 = libxaos::linear::Matrix<int, 3, 3>;
using IntMatrix4 = libxaos::linear::Matrix<int, 4, 4>;
using IntVector3 = libxaos::linear::Vector<int, 3>;

using FloatMatrix4 = libxaos::linear::Matrix<float, 4, 4>;

TEST_CASE("MATHS:LINEAR/Matrix | Can Create Matrices", "[maths]") {
    IntMatrix3 mat1 {IntMatrix3::ZERO};
    IntMatrix3 mat2 {IntMatrix3::IDENTITY};
    IntMatrix3 mat3 {
        {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        }
    };

    for (int col = 0; col < 3; col++) {
        for (int row = 0; row < 3; row++) {
            // Check mat1
            REQUIRE(mat1[col][row] == 0);

            // Check mat2
            int val = row == col ? 1 : 0;
            REQUIRE((mat2[col][row] == val));

            // Check mat3
            REQUIRE((mat3[col][row] == (row * 3 + col + 1)));
        }
    }
}

TEST_CASE("MATHS:LINEAR/Matrix | Can Access Columns by reference", "[maths]") {
    IntMatrix3 mat {
        {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        }
    };

    IntMatrix3::ColumnType col0 = mat[0];
    IntMatrix3::ColumnType col1 = mat.at(1);
    mat[2] = IntMatrix3::ColumnType{1, 2, 3};

    REQUIRE_THROWS_AS((mat.at(3)), std::out_of_range);

    REQUIRE((col0 == IntMatrix3::ColumnType{1, 4, 7}));
    REQUIRE((col1 == IntMatrix3::ColumnType{2, 5, 8}));
    REQUIRE((mat[2] == IntMatrix3::ColumnType{1, 2, 3}));
}

TEST_CASE("MATHS:LINEAR/Matrix | Can Access Columns", "[maths]") {
    IntMatrix3 mat {
        {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        }
    };

    IntMatrix3::ColumnType col0 = mat.getColumn(0);
    IntMatrix3::ColumnType col1 = mat.getColumnChecked(1);

    REQUIRE_THROWS_AS((mat.getColumnChecked(3)), std::out_of_range);

    REQUIRE((col0 == IntMatrix3::ColumnType{1, 4, 7}));
    REQUIRE((col1 == IntMatrix3::ColumnType{2, 5, 8}));
}

TEST_CASE("MATHS:LINEAR/Matrix | Can Access Rows", "[maths]") {
    IntMatrix3 mat {
        {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        }
    };

    IntMatrix3::RowType row0 = mat.getRow(0);
    IntMatrix3::RowType row1 = mat.getRowChecked(1);

    REQUIRE_THROWS_AS((mat.getRowChecked(3)), std::out_of_range);

    REQUIRE((row0 == IntMatrix3::RowType{1, 2, 3}));
    REQUIRE((row1 == IntMatrix3::RowType{4, 5, 6}));
}

TEST_CASE("MATHS:LINEAR/Matrix | Can Compare Matrices", "[maths]") {
    IntMatrix3 mat1 {IntMatrix3::ZERO};
    IntMatrix3 mat2 {IntMatrix3::ZERO};
    IntMatrix3 mat3 {IntMatrix3::IDENTITY};

    REQUIRE(mat1 == mat2);
    REQUIRE(mat1 != mat3);
}

TEST_CASE("MATHS:LINEAR/Matrix | Can Transpose Matrices", "[maths]") {
    IntMatrix3 mat1 {
        {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        }
    };
    IntMatrix3 mat2 {
        {
            {1, 4, 7},
            {2, 5, 8},
            {3, 6, 9}
        }
    };
    IntMatrix3 mat3 = mat2;
    IntMatrix3 mat1T = getTranspose(mat1);
    transpose(mat3);

    REQUIRE(mat1T == mat2);
    REQUIRE(mat3 == mat1);
}

TEST_CASE("MATHS:LINEAR/Matrix | Can Inverse Matrices", "[maths]") {
    FloatMatrix4 mat1 {
        {
            {1,  2,  3,  4},
            {5,  6,  7,  8},
            {9,  10, 11, 12},
            {13, 14, 15, 16}
        }
    }; // uninvertible
    FloatMatrix4 mat2 {
        {
            {1, 0, 1, 3},
            {2, 4, 5, 7},
            {9, 8, 0, 0},
            {0, 1, 1, 2}
        }
    };

    FloatMatrix4 mat3 = mat2 * getInverse(mat2);
    REQUIRE_THROWS_AS(invert(mat1), libxaos::linear::MatrixUninvertible);

    // Manually check because direct equals compare with floats is BAD
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            float val = (col == row) ? 1 : 0;

            REQUIRE(mat3[col][row] - val < 0.001F);
        }
    }
}

TEST_CASE("MATHS:LINEAR/Matrix | Can Negate Matrices", "[maths]") {
    IntMatrix3 mat1 {
        {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        }
    };
    IntMatrix3 mat2 {
        {
            {-1, -2, -3},
            {-4, -5, -6},
            {-7, -8, -9}
        }
    };

    REQUIRE(-mat1 == mat2);
}

TEST_CASE("MATHS:LINEAR/Matrix | Can Add Matrices", "[maths]") {
    IntMatrix3 mat1 {
        {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        }
    };
    IntMatrix3 mat2 {
        {
            { 2,  4,  6},
            { 8, 10, 12},
            {14, 16, 18}
        }
    };

    IntMatrix3 mat3 = mat1 + mat1;
    mat1 += mat1;

    REQUIRE(mat1 == mat2);
    REQUIRE(mat3 == mat2);
}

TEST_CASE("MATHS:LINEAR/Matrix | Can Subtract Matrices", "[maths]") {
    IntMatrix3 mat1 {
        {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        }
    };
    IntMatrix3 mat2 {IntMatrix3::ZERO};

    IntMatrix3 mat3 = mat1 - mat1;
    mat1 -= mat1;

    REQUIRE(mat1 == mat2);
    REQUIRE(mat3 == mat2);
}

TEST_CASE("MATHS:LINEAR/Matrix | Can Divide Matrices by Primitives", "[maths]") {
    FloatMatrix4 mat1 {
        {
            { 2,  4,  6,  8},
            {10, 12, 14, 16},
            {18, 20, 22, 24},
            {26, 28, 30, 32}
        }
    };
    FloatMatrix4 mat2 {
        {
            { 3,  6,  9, 12},
            {15, 18, 21, 24},
            {27, 30, 33, 36},
            {39, 42, 45, 48}
        }
    };
    FloatMatrix4 ans {
        {
            { 1,  2,  3,  4},
            { 5,  6,  7,  8},
            { 9, 10, 11, 12},
            {13, 14, 15, 16}
        }
    };

    FloatMatrix4 mat3 = mat1 / 2.0F;
    mat2 /= 3.0F;

    REQUIRE(mat3 == ans);
    REQUIRE(mat2 == ans);
}

TEST_CASE("MATHS:LINEAR/Matrix | Matrix Multiplication", "[maths]") {
    IntMatrix3 mat1 {
        {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        }
    };
    IntMatrix3 mat2 {
        {
            {30,  36,  42},
            {66,  81,  96},
            {102, 126, 150}
        }
    };
    IntMatrix3 mat3 = mat1;

    IntMatrix3 mat4 = mat1 * mat1;
    mat3 *= mat1;

    REQUIRE(mat4 == mat2);
    REQUIRE(mat3 == mat2);
}

TEST_CASE("MATHS:LINEAR/Matrix | Matrix and Primitive Multiplication", "[maths]") {
    IntMatrix3 mat1 {
        {
            {1, 4, 7},
            {2, 5, 8},
            {3, 6, 9}
        }
    };
    IntMatrix3 mat2 {
        {
            {2, 8,  14},
            {4, 10, 16},
            {6, 12, 18}
        }
    };
    IntMatrix3 mat3 {
        {
            {3, 12, 21},
            {6, 15, 24},
            {9, 18, 27}
        }
    };
    IntMatrix3 mat4 = mat1;
    IntMatrix3 mat5 {
        {
            {4,  16, 28},
            {8,  20, 32},
            {12, 24, 36}
        }
    };

    REQUIRE(mat1 * 2 == mat2);
    REQUIRE(3 * mat1 == mat3);
    mat4 *= 4;
    REQUIRE(mat4 == mat5);
}

TEST_CASE("MATHS:LINEAR/Matrix | Matrix and Vector Multiplication", "[maths]") {
    IntMatrix3 mat {
        {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        }
    };
    IntVector3 vec {1, 2, 3};

    REQUIRE((mat * vec == IntVector3{14, 32, 50}));
    REQUIRE((vec * mat == IntVector3{30, 36, 42}));
}

TEST_CASE("MATHS:LINEAR/Matrix | Matrices are 'resizable'", "[maths]") {
    IntMatrix3 mat1 {
        {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        }
    };
    IntMatrix2 mat2 {
        {
            {1, 2},
            {4, 5}
        }
    };
    IntMatrix4 mat3 {
        {
            {1, 2, 3, 0},
            {4, 5, 6, 0},
            {7, 8, 9, 0},
            {0, 0, 0, 0}
        }
    };

    REQUIRE((libxaos::linear::getResized<2, 2>(mat1, 0, 0) == mat2));
    REQUIRE((libxaos::linear::getResized<4, 4>(mat1, 0, 0) == mat3));
}
