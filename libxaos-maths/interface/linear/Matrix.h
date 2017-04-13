#ifndef     LIBXAOS_MATHS_LINEAR_MATRIX_H
#define     LIBXAOS_MATHS_LINEAR_MATRIX_H

#include <initializer_list>
#include <type_traits>

#include "linear/Vector.h"

namespace libxaos {
    namespace linear {

        /**
         *  @brief This class represenets an MxN matrix.
         *
         *  This class represents an M column, N row matrix.  Its memory
         *  is laid out in COLUMN MAJOR order in order to be compatible
         *  with the OpenGL graphics library.  As such, accessing matrix
         *  memory with `myMatrix[1][2]` returns the data in the first COLUMN
         *  and SECOND row.
         *
         *  Underneath the hood, the matrix data is actually M number of
         *  N-length vectors.  This simplifies some of its implementation.
         *
         *  This class allows the creation of row or column "matricies" though
         *  it is recommended that one use Vectors for that unless one wants
         *  to avoid the "duplicity" that a Vector may be either depending on
         *  how it is combined with a matrix (left or right multiplication).
         *
         *  @tparam T the numeric type of objects contained within the Matrix.
         *  @tparam M the number of columns in this matrix
         *  @tparam N the number of rows in this matrix
         */
        template<typename T, unsigned int M, unsigned int N>
        class Matrix {
            static_assert(std::is_arithmetic<T>::value,
                    "Matrix types must be arithmetic!");
            static_assert(M > 0, "Column count must be non-zero!");
            static_assert(N > 0, "Row count must be non-zero!");

            public:
                typedef Vector<T, N> ColumnType;
                typedef Vector<T, M> RowType;

                //! Used for Constructing new Matrices
                enum InitializationType {
                    ZERO,
                    IDENTITY
                };

                //! Creates a new Matrix based on the Initialization type.
                explicit Matrix(InitializationType);
                //! Creates a new Matrix from a nested initializer list
                //! Note that the data is initialized such that typing it
                //! out looks like the matrix itself.  That is, the nested
                //! lists are ROWS... as typing it out as such looks like a
                //! proper matrix.
                //! Any missing data is interpreted as 0.  Any extra data is
                //! ignored.
                explicit Matrix(
                        std::initializer_list<std::initializer_list<T>>);
                ~Matrix();

                Matrix(const Matrix<T, M, N>&);
                Matrix<T, M, N>& operator=(const Matrix<T, M, N>&);
                Matrix(Matrix<T, M, N>&&);
                Matrix<T, M, N>& operator=(Matrix<T, M, N>&&);

                //! Accesses a column by reference
                inline ColumnType& operator[](unsigned int);
                //! Accesses a column by const reference
                inline const ColumnType& operator[](unsigned int) const;
                //! Accesses a column by reference safely
                inline ColumnType& at(unsigned int);
                //! Accesses a column by const reference safely
                inline const ColumnType& at(unsigned int) const;

                //! Gets a Column of the Matrix
                inline ColumnType getColumn(unsigned int) const;
                //! Gets a Column of the Matrix safely
                inline ColumnType getColumnChecked(unsigned int) const;

                //! Gets a Row of the Matrix
                inline RowType getRow(unsigned int) const;
                //! Gets a Row of the Matrix safely
                inline RowType getRowChecked(unsigned int) const;

            private:
                ColumnType _data[M];
        };

        //! Compares two matrices (equality)
        template<typename T, unsigned int M, unsigned int N>
        inline bool operator==(const Matrix<T, M, N>&, const Matrix<T, M, N>&);
        //! Compares two matrices (inequality)
        template<typename T, unsigned int M, unsigned int N>
        inline bool operator!=(const Matrix<T, M, N>&, const Matrix<T, M, N>&);

        //! Gets the Transpose of a Matrix
        template<typename T, unsigned int M, unsigned int N>
        inline Matrix<T, N, M> getTranspose(const Matrix<T, M, N>&);
        //! Transposes the passed in square Matrix "in place"
        template<typename T, unsigned int N>
        inline void transpose(Matrix<T, N, N>&);

        //! Gets the Inverse of a square Matrix (may throw)
        template<typename T, unsigned int N>
        inline Matrix<T, N, N> getInverse(const Matrix<T, N, N>&);
        //! Inverses a Matrix "in place" (may throw)
        template<typename T, unsigned int N>
        void invert(Matrix<T, N, N>&);

        //! Handles Matrix negation
        template<typename T, unsigned int M, unsigned int N>
        inline Matrix<T, M, N> operator-(const Matrix<T, M, N>&);

        //! Handles Matrix addition
        template<typename T, unsigned int M, unsigned int N>
        inline Matrix<T, M, N> operator+(const Matrix<T, M, N>&,
                const Matrix<T, M, N>&);
        //! Handles Matrix addition assignment
        template<typename T, unsigned int M, unsigned int N>
        inline Matrix<T, M, N>& operator+=(Matrix<T, M, N>&,
                const Matrix<T, M, N>&);

        //! Handles Matrix subtraction
        template<typename T, unsigned int M, unsigned int N>
        inline Matrix<T, M, N> operator-(const Matrix<T, M, N>&,
                const Matrix<T, M, N>&);
        //! Handles Matrix subtraction assignment
        template<typename T, unsigned int M, unsigned int N>
        inline Matrix<T, M, N>& operator-=(Matrix<T, M, N>&,
                const Matrix<T, M, N>&);

        //! Handles Matrix by primitive division
        template<typename T, unsigned int M, unsigned int N>
        inline Matrix<T, M, N> operator/(const Matrix<T, M, N>&, T);
        //! Handles Matrix by primitive division assignment
        template<typename T, unsigned int M, unsigned int N>
        inline Matrix<T, M, N>& operator/=(Matrix<T, M, N>&, T);

        //! Handles Matrix multiplication: (column x row) MxN * OxM = OxN
        template<typename T, unsigned int M, unsigned int N, unsigned int O>
        inline Matrix<T, O, N> operator*(const Matrix<T, M, N>&,
                const Matrix<T, O, M>&);
        //! Handles square Matrix multiplication assignment
        template<typename T, unsigned int N>
        inline Matrix<T, N, N>& operator*=(Matrix<T, N, N>&,
                const Matrix<T, N, N>&);

        //! Handles Matrix by primitive multiplication
        template<typename T, unsigned int M, unsigned int N>
        inline Matrix<T, M, N> operator*(const Matrix<T, M, N>&, T);
        //! Handles Matrix by primitive multiplication assignment
        template<typename T, unsigned int M, unsigned int N>
        inline Matrix<T, M, N>& operator*=(Matrix<T, M, N>&, T);
        //! Handles primitive by Matrix multiplication
        template<typename T, unsigned int M, unsigned int N>
        inline Matrix<T, M, N> operator*(T, const Matrix<T, M, N>&);

        //! Handles (row) Vector by Matrix mupltiplication (vec * mat)
        template<typename T, unsigned int M, unsigned int N>
        inline Vector<T, M> operator*(const Vector<T, N>&,
                const Matrix<T, M, N>&);
        //! Handles Matrix by (column) Vector multiplication (mat * vec)
        template<typename T, unsigned int M, unsigned int N>
        inline Vector<T, N> operator*(const Matrix<T, M, N>&,
                const Vector<T, M>&);

        //! Gets a SubMatrix (or a SuperMatrix filled with 0's) of a Matrix
        //! Use it like: `getResized<3, 5>(myMat);` (<col, row>)
        template<unsigned int O, unsigned int P, typename T, unsigned int M,
                unsigned int N>
        inline Matrix<T, O, P> getResized(const Matrix<T, M, N>&, unsigned int,
                unsigned int);

        //! Exception for when one attempts to invert an uninvertible matrix
        //! @todo A proper exceptions namespace
        struct MatrixUninvertible {};
    }
}

// pull in implementations
#include "Matrix-tpp.h"

#endif   // LIBXAOS_MATHS_LINEAR_MATRIX_H
