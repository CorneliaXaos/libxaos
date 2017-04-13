/**
 *  @file Matrix-tpp.h
 *  @brief Implementations for the Matrix template class.
 */

#include <algorithm>
#include <cassert>
#include <exception>
#include <initializer_list>
#include <utility>

namespace libxaos {
    namespace linear {

        // Constructors
        template<typename T, unsigned int M, unsigned int N>
        Matrix<T, M, N>::Matrix(Matrix<T, M, N>::InitializationType type) {
            if (type == IDENTITY) {
                unsigned int index = 0;
                while (index < M && index < N) {
                    _data[index][index] = T{1};
                    index++;
                }
            }
            // we don't have to initialize teh zero.. that's default
            // for numeric types
        }
        template<typename T, unsigned int M, unsigned int N>
        Matrix<T, M, N>::Matrix(
                std::initializer_list<std::initializer_list<T>> data) {
            int rowIndex = 0;
            for (std::initializer_list<T> row : data) {
                int colIndex = 0;
                for (T val : row) {
                    _data[colIndex++][rowIndex] = val;
                    if (colIndex == M) break;
                }
                if (++rowIndex == N) break;
            }
        }
        template<typename T, unsigned int M, unsigned int N>
        Matrix<T, M, N>::~Matrix() {
            // nothing to do.. thankfully... :P
        }

        // Copy / Move Semantics
        template<typename T, unsigned int M, unsigned int N>
        Matrix<T, M, N>::Matrix(const Matrix<T, M, N>& other) {
            std::copy(other._data, other._data + M, _data);
        }
        template<typename T, unsigned int M, unsigned int N>
        Matrix<T, M, N>& Matrix<T, M, N>::operator=(
                const Matrix<T, M, N>& other) {
            if (this != &other) {
                std::copy(other._data, other._data + M, _data);
            }
            return *this;
        }
        template<typename T, unsigned int M, unsigned int N>
        Matrix<T, M, N>::Matrix(Matrix<T, M, N>&& other) {
            // since there's no pointer / resource data we can just copy again
            std::copy(other._data, other._data + M, _data);
        }
        template<typename T, unsigned int M, unsigned int N>
        Matrix<T, M, N>& Matrix<T, M, N>::operator=(Matrix<T, M, N>&& other) {
            // same as above
            if (this != &other) {
                std::copy(other._data, other._data + M, _data);
            }
            return *this;
        }

        // Reference Column Access
        template<typename T, unsigned int M, unsigned int N>
        inline typename Matrix<T, M, N>::ColumnType&
                Matrix<T, M, N>::operator[](unsigned int index) {
            return _data[index];
        }
        template<typename T, unsigned int M, unsigned int N>
        inline const typename Matrix<T, M, N>::ColumnType&
                Matrix<T, M, N>::operator[](unsigned int index) const {
            return _data[index];
        }
        template<typename T, unsigned int M, unsigned int N>
        inline typename Matrix<T, M, N>::ColumnType& Matrix<T, M, N>::at(
                unsigned int index) {
            if (index >= M)
                throw std::out_of_range{"Column index out of bounds."};
            return _data[index];
        }
        template<typename T, unsigned int M, unsigned int N>
        inline const typename Matrix<T, M, N>::ColumnType& Matrix<T, M, N>::at(
                unsigned int index) const {
            if (index >= M)
                throw std::out_of_range{"Column index out of bounds."};
            return _data[index];
        }

        // Value Column Access
        template<typename T, unsigned int M, unsigned int N>
        inline typename Matrix<T, M, N>::ColumnType Matrix<T, M, N>::getColumn(
                unsigned int index) const {
            return _data[index];
        }
        template<typename T, unsigned int M, unsigned int N>
        inline typename Matrix<T, M, N>::ColumnType
                Matrix<T, M, N>::getColumnChecked( unsigned int index) const {
            if (index >= M)
                throw std::out_of_range{"Column index out of bounds."};
            return _data[index];
        }

        // Value Row Access
        template<typename T, unsigned int M, unsigned int N>
        inline typename Matrix<T, M, N>::RowType Matrix<T, M, N>::getRow(
                unsigned int index) const {
            RowType row {};
            for (unsigned int colIndex = 0; colIndex < N; colIndex++) {
                row[colIndex] = _data[colIndex][index];
            }
            return row;
        }
        template<typename T, unsigned int M, unsigned int N>
        inline typename Matrix<T, M, N>::RowType Matrix<T, M, N>::getRowChecked(
                unsigned int index) const {
            if (index >= N)
                throw std::out_of_range{"Row index out of bounds."};
            return getRow(index);
        }

        // Comparison Operators
        template<typename T, unsigned int M, unsigned int N>
        inline bool operator==(const Matrix<T, M, N>& a, const Matrix<T, M, N>& b) {
            for (unsigned int col = 0; col < M; col++) {
                auto aCol = a.getColumn(col);
                auto bCol = b.getColumn(col);
                if (aCol != bCol)
                    return false;
            }
            return true;
        }
        template<typename T, unsigned int M, unsigned int N>
        inline bool operator!=(const Matrix<T, M, N>& a, const Matrix<T, M, N>& b) {
            return !(a == b);
        }

        // Transposition
        template<typename T, unsigned int M, unsigned int N>
        inline Matrix<T, N, M> getTranspose(const Matrix<T, M, N>& mat) {
            Matrix<T, N, M> ret {Matrix<T, N, M>::ZERO};
            for (unsigned int rowIndex = 0; rowIndex < N; rowIndex++) {
                ret[rowIndex] = mat.getRow(rowIndex);
            }
            return ret;
        }
        template<typename T, unsigned int N>
        inline void transpose(Matrix<T, N, N>& mat) {
            mat = getTranspose(mat); // LAZY :P
        }

        // Inversion
        template<typename T, unsigned int N>
        inline Matrix<T, N, N> getInverse(const Matrix<T, N, N>& mat) {
            Matrix<T, N, N> ret = mat;
            invert(ret);
            return ret;
        }
        template<typename T, unsigned int N>
        void invert(Matrix<T, N, N>& mat) {
            // Column Augment with identity:
            Matrix<T, N, N * 2> augmented = getResized<N, N * 2>(mat, 0, 0);
            for (unsigned int index = 0; index < N; index++) {
                augmented[index][N + index] = T{1};
            }

            // Now... the tough part...  Gaussian Eliminate the upper square
            for (unsigned int col = 0; col < N; col++) { // iterate through all columns
                int swapTarget = col + 1;
                while (!(augmented[col][col] < T{0} ||
                        augmented[col][col] > T{0})) {
                    if (swapTarget == N) // our only edge case
                        throw MatrixUninvertible{};

                    // Now swap the current column with the target and try again
                    auto current = augmented.getColumn(col);
                    auto target = augmented.getColumn(swapTarget);
                    augmented[col] = current;
                    augmented[swapTarget] = current;

                    swapTarget++;
                }

                // If we get here we have a non-zero value we can work with
                // First, make it '1' if it isn't
                if (augmented[col][col] > T{1} ||
                        augmented[col][col] < T{1}) {
                    augmented[col] /= augmented[col][col];
                }

                // Now, iterate through the columns and cancel out in same row
                for (unsigned int index = 0; index < N; index++) {
                    if (index == col) continue; // skip the current column

                    auto val = augmented[index][col];
                    if (augmented[index][col] > T{0} ||
                            augmented[index][col] < T{0}) {
                        augmented[index] -= val * augmented[col];
                    }
                }

                // Now loop and repeat until the end...
            }

            // Finally, extract the augmented matrix.  It is the inverse.
            mat = getResized<N, N>(augmented, 0, N);
        }

        // Negation
        template<typename T, unsigned int M, unsigned int N>
        inline Matrix<T, M, N> operator-(const Matrix<T, M, N>& mat) {
            Matrix<T, M, N> ret = mat;
            for (unsigned int col = 0; col < M; col++) {
                ret[col] = -ret[col];
            }
            return ret;
        }

        // Matrix Addition
        template<typename T, unsigned int M, unsigned int N>
        inline Matrix<T, M, N> operator+(const Matrix<T, M, N>& a,
                const Matrix<T, M, N>& b) {
            Matrix<T, M, N> ret = a;
            return ret += b;
        }
        template<typename T, unsigned int M, unsigned int N>
        inline Matrix<T, M, N>& operator+=(Matrix<T, M, N>& a,
                const Matrix<T, M, N>& b) {
            for (unsigned int col = 0; col < M; col++) {
                a[col] += b[col];
            }
            return a;
        }

        // Matrix Subtraction
        template<typename T, unsigned int M, unsigned int N>
        inline Matrix<T, M, N> operator-(const Matrix<T, M, N>& a,
                const Matrix<T, M, N>& b) {
            Matrix<T, M, N> ret = a;
            return ret -= b;
        }
        template<typename T, unsigned int M, unsigned int N>
        inline Matrix<T, M, N>& operator-=(Matrix<T, M, N>& a,
                const Matrix<T, M, N>& b) {
            for (unsigned int col = 0; col < M; col++) {
                a[col] -= b[col];
            }
            return a;
        }

        // Matrix / primitive Division
        template<typename T, unsigned int M, unsigned int N>
        inline Matrix<T, M, N> operator/(const Matrix<T, M, N>& mat, T val) {
            Matrix<T, M, N> ret = mat;
            return ret /= val;
        }
        template<typename T, unsigned int M, unsigned int N>
        inline Matrix<T, M, N>& operator/=(Matrix<T, M, N>& mat, T val) {
            assert(val < T{0} || val > T{0});
            for (unsigned int col = 0; col < M; col++) {
                mat[col] /= val;
            }
            return mat;
        }

        // Matrix multiplication
        template<typename T, unsigned int M, unsigned int N, unsigned int O>
        inline Matrix<T, O, N> operator*(const Matrix<T, M, N>& a,
                const Matrix<T, O, M>& b) {
            Matrix<T, O, N> ret {};
            for (unsigned int rowIndex = 0; rowIndex < N; rowIndex++) {
                for (unsigned int colIndex = 0; colIndex < O; colIndex++) {
                    auto row = a.getRow(rowIndex);
                    auto col = b.getColumn(colIndex);
                    ret[colIndex][rowIndex] = dot(row, col);
                }
            }
            return ret;
        }
        template<typename T, unsigned int N>
        inline Matrix<T, N, N>& operator*=(Matrix<T, N, N>& a,
                const Matrix<T, N, N>& b) {
            a = a * b; // yea... simplest I can do
            return a;
        }

        // Matrix by primitive Multiplication
        template<typename T, unsigned int M, unsigned int N>
        inline Matrix<T, M, N> operator*(const Matrix<T, M, N>& mat, T val) {
            Matrix<T, M, N> ret = mat;
            return ret *= val;
        }
        template<typename T, unsigned int M, unsigned int N>
        inline Matrix<T, M, N>& operator*=(Matrix<T, M, N>& mat, T val) {
            for (unsigned int col = 0; col < M; col++) {
                mat[col] *= val;
            }
            return mat;
        }
        template<typename T, unsigned int M, unsigned int N>
        inline Matrix<T, M, N> operator*(T val, const Matrix<T, M, N>& mat) {
            return mat * val;
        }

        // Matrix by vector multiplication
        template<typename T, unsigned int M, unsigned int N>
        inline Vector<T, M> operator*(const Vector<T, N>& vec,
                const Matrix<T, M, N>& mat) {
            Vector<T, M> ret {};
            for (unsigned int col = 0; col < M; col++) {
                ret[col] = dot(vec, mat.getColumn(col));
            }
            return ret;
        }
        template<typename T, unsigned int M, unsigned int N>
        inline Vector<T, N> operator*(const Matrix<T, M, N>& mat,
                const Vector<T, M>& vec) {
            Vector<T, N> ret {};
            for (unsigned int row = 0; row < M; row++) {
                ret[row] = dot(mat.getRow(row), vec);
            }
            return ret;
        }

        // Sub / Super Matrix operation
        template<unsigned int O, unsigned int P, typename T, unsigned int M,
                unsigned int N>
        inline Matrix<T, O, P> getResized(const Matrix<T, M, N>& mat,
                unsigned int colIndex, unsigned int rowIndex) {
            Matrix<T, O, P> ret {Matrix<T, O, P>::ZERO};
            for (unsigned int col = 0; col < O && col + colIndex < M; col++) {
                for (unsigned int row = 0; row < P && row + rowIndex < N;
                        row++) {
                    ret[col][row] = mat[col + colIndex][row + rowIndex];
                }
            }
            return ret;
        }

    }
}
