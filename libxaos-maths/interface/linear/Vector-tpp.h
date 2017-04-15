/**
 *  @file Vector-tpp.h
 *  @brief Implementations for the Vector template class
 */

#include <cassert>
#include <cmath>
#include <stdexcept>
#include <utility>

namespace libxaos {
    namespace linear {

        // Constructors
        template<typename T, unsigned int N>
        Vector<T, N>::Vector() : _data(std::valarray<T>(N)) {} // Defaults
        template<typename T, unsigned int N>
        Vector<T, N>::Vector(std::initializer_list<T> init) : Vector<T, N>{} {
            int index = 0;
            for (T val : init) {
                _data[index++] = val;
                if (index == N) break;
            }
        }
        template<typename T, unsigned int N>
        Vector<T, N>::Vector(T val) : Vector<T, N>{} {
            for (unsigned int i = 0; i < N; i++) {
                _data[i] = val;
            }
        }
        template<typename T, unsigned int N>
        Vector<T, N>::~Vector() {} // Nothing to do.

        // Copy and Move Semantics
        template<typename T, unsigned int N>
        Vector<T, N>::Vector(const Vector<T, N>& other) : _data(other._data) {}
        template<typename T, unsigned int N>
        Vector<T, N>& Vector<T, N>::operator=(const Vector<T, N>& other) {
            if (this != &other) {
                _data = other._data;
            }
            return *this;
        }
        template<typename T, unsigned int N>
        Vector<T, N>::Vector(Vector<T, N>&& other) :
                _data(std::move(other._data)) {}
        template<typename T, unsigned int N>
        Vector<T, N>& Vector<T,N>::operator=(Vector<T, N>&& other) {
            if (this != &other) {
                _data = std::move(other._data);
            }
            return *this;
        }

        // Accessors (Get and Set)
        template<typename T, unsigned int N>
        template<int M>
        inline EnableIf<HasIndex(M, 0), T> Vector<T, N>::x() const {
            return (*this)[0];
        }
        template<typename T, unsigned int N>
        template<int M>
        inline EnableIf<HasIndex(M, 0), void> Vector<T, N>::x(T val) {
            (*this)[0] = val;
        }

        template<typename T, unsigned int N>
        template<int M>
        inline EnableIf<HasIndex(M, 1), T> Vector<T, N>::y() const {
            return (*this)[1];
        }
        template<typename T, unsigned int N>
        template<int M>
        inline EnableIf<HasIndex(M, 1), void> Vector<T, N>::y(T val) {
            (*this)[1] = val;
        }

        template<typename T, unsigned int N>
        template<int M>
        inline EnableIf<HasIndex(M, 2), T> Vector<T, N>::z() const {
            return (*this)[2];
        }
        template<typename T, unsigned int N>
        template<int M>
        inline EnableIf<HasIndex(M, 2), void> Vector<T, N>::z(T val) {
            (*this)[2] = val;
        }

        template<typename T, unsigned int N>
        inline T& Vector<T, N>::operator[](unsigned int index) {
            return _data[index];
        }
        template<typename T, unsigned int N>
        inline const T& Vector<T, N>::operator[](unsigned int index) const {
            return _data[index];
        }

        template<typename T, unsigned int N>
        inline T& Vector<T, N>::at(unsigned int index) {
            if (index >= N)
                throw std::out_of_range{"Bad Vector Index!"};
            return (*this)[index];
        }
        template<typename T, unsigned int N>
        inline const T& Vector<T, N>::at(unsigned int index) const {
            if (index >= N)
                throw std::out_of_range{"Bad Vector Index!"};
            return (*this)[index];
        }

        // Vector (In)Equality
        template<typename T, unsigned int N>
        inline bool operator==(const Vector<T, N>& a,
                const Vector<T, N>& b) {
            std::valarray<bool> intermediate = a._data == b._data;
            return intermediate.min() == true;
        }
        template<typename T, unsigned int N>
        inline bool operator!=(const Vector<T, N>& a, const Vector<T, N>& b) {
            return !(a == b);
        }

        // Vector Negation
        template<typename T, unsigned int N>
        inline Vector<T, N> operator-(const Vector<T, N>& vec) {
            Vector<T, N> ret = vec;
            ret._data = -ret._data;
            return ret;
        }

        // Vector Scaling (Multiplication)
        template<typename T, unsigned int N>
        inline Vector<T, N> operator*(const Vector<T, N>& vec, T scale) {
            Vector<T, N> ret = vec;
            ret *= scale;
            return ret;
        }
        template<typename T, unsigned int N>
        inline Vector<T, N> operator*(T scale, const Vector<T, N>& vec) {
            return vec * scale;
        }
        template<typename T, unsigned int N>
        inline Vector<T, N>& operator*=(Vector<T, N>& vec, T scale) {
            vec._data *= scale;
            return vec;
        }

        // Vector Scaling (Division)
        template<typename T, unsigned int N>
        inline Vector<T, N> operator/(const Vector<T, N>& vec, T scale) {
            Vector<T, N> ret = vec;
            ret /= scale;
            return ret;
        }
        template<typename T, unsigned int N>
        inline Vector<T, N>& operator/=(Vector<T, N>& vec, T scale) {
            vec._data /= scale;
            return vec;
        }

        // Vector Addition
        template<typename T, unsigned int N>
        inline Vector<T, N> operator+(const Vector<T, N>& a,
                const Vector<T, N>& b) {
            Vector<T, N> ret = a;
            ret += b;
            return ret;
        }
        template<typename T, unsigned int N>
        inline Vector<T, N>& operator+=(Vector<T, N>& a,
                const Vector<T, N>& b) {
            a._data += b._data;
            return a;
        }
        template<typename T, unsigned int N>
        inline Vector<T, N> operator+(const Vector<T, N>& vec, T summand) {
            Vector<T, N> ret = vec;
            ret += Vector<T, N>(summand);
            return ret;
        }
        template<typename T, unsigned int N>
        inline Vector<T, N> operator+(T summand, const Vector<T, N>& vec) {
            return vec + summand;
        }

        // Vector Subtraction
        template<typename T, unsigned int N>
        inline Vector<T, N> operator-(const Vector<T, N>& a,
                const Vector<T, N>& b) {
            Vector<T, N> ret = a;
            ret -= b;
            return ret;
        }
        template<typename T, unsigned int N>
        inline Vector<T, N>& operator-=(Vector<T, N>& a,
                const Vector<T, N>& b) {
            a._data -= b._data;
            return a;
        }
        template<typename T, unsigned int N>
        inline Vector<T, N> operator-(const Vector<T, N>& vec, T subtrahend) {
            Vector<T, N> ret = vec;
            ret -= Vector<T, N>(subtrahend);
            return ret;
        }

        // Magnitude Calucaltions
        template<typename T, unsigned int N>
        inline T magnitude(const Vector<T, N>& vec) {
            // return sqrt(magnitude2(vec)); // ALSO DAMMIT, MSVC...
            return static_cast<T>(sqrt(magnitude2(vec)));
        }
        template<typename T, unsigned int N>
        inline T magnitude2(const Vector<T, N>& vec) {
            return dot(vec, vec); // this is a neat little trick
        }

        // Special Products
        template<typename T, unsigned int N>
        inline T dot(const Vector<T, N>& a, const Vector<T, N>& b) {
            std::valarray<T> mult = a._data * b._data;
            return mult.sum();
        }
        template<typename T>
        inline Vector<T, 3U> cross(const Vector<T, 3>& a,
                const Vector<T, 3>& b) {
            Vector<T, 3> ret {};
            ret.x(a[1] * b[2] - a[2] * b[1]);
            ret.y(a[2] * b[0] - a[0] * b[2]);
            ret.z(a[0] * b[1] - a[1] * b[0]);
            return ret;
        }

        // Normalization
        template<typename T, unsigned int N>
        inline Vector<T, N> getNormalized(const Vector<T, N>& other) {
            Vector<T, N> ret {other};
            normalize(ret);
            return ret;
        }
        template<typename T, unsigned int N>
        inline void normalize(Vector<T, N>& vec) {
            T mag = magnitude(vec);
            assert(mag > T{0} || mag < T{0});
            vec /= mag;
        }
    }
}
