/**
 *  @file Vector-tpp.h
 *  @brief Implementations for the Vector template class
 */

 #include <cmath>
 #include <utility>

namespace libxaos {
    namespace maths {

        // Constructors
        template<typename T, int N>
        Vector<T, N>::Vector() : _data(std::array<T, N>{}) {} // Defaults
        template<typename T, int N>
        Vector<T, N>::Vector(std::initializer_list<T> init) : Vector<T, N>() {
            int index = 0;
            for (T val : init) {
                _data[index++] = val;
            }
        }
        template<typename T, int N>
        Vector<T, N>::~Vector() {} // Nothing to do.

        // Copy and Move Semantics
        template<typename T, int N>
        Vector<T, N>::Vector(const Vector<T, N>& other) : _data(other._data) {}
        template<typename T, int N>
        Vector<T, N>& Vector<T, N>::operator=(const Vector<T, N>& other) {
            if (this != &other) {
                _data = other._data;
            }
            return *this;
        }
        template<typename T, int N>
        Vector<T, N>::Vector(Vector<T, N>&& other) :
                _data(std::move(other._data)) {}
        template<typename T, int N>
        Vector<T, N>& Vector<T,N>::operator=(Vector<T, N>&& other) {
            if (this != &other) {
                _data = std::move(other._data);
            }
            return *this;
        }

        // Accessors (Get and Set)
        template<typename T, int N>
        template<int M>
        inline EnableIf<HasIndex(M, 0), T> Vector<T, N>::x() const {
            return (*this)[0];
        }
        template<typename T, int N>
        template<int M>
        inline EnableIf<HasIndex(M, 0), void> Vector<T, N>::x(T val) {
            (*this)[0] = val;
        }

        template<typename T, int N>
        template<int M>
        inline EnableIf<HasIndex(M, 1), T> Vector<T, N>::y() const {
            return (*this)[1];
        }
        template<typename T, int N>
        template<int M>
        inline EnableIf<HasIndex(M, 1), void> Vector<T, N>::y(T val) {
            (*this)[1] = val;
        }

        template<typename T, int N>
        template<int M>
        inline EnableIf<HasIndex(M, 2), T> Vector<T, N>::z() const {
            return (*this)[2];
        }
        template<typename T, int N>
        template<int M>
        inline EnableIf<HasIndex(M, 2), void> Vector<T, N>::z(T val) {
            (*this)[2] = val;
        }

        template<typename T, int N>
        inline T& Vector<T, N>::operator[](int index) {
            return _data[index];
        }
        template<typename T, int N>
        inline const T& Vector<T, N>::operator[](int index) const {
            return _data[index];
        }

        template<typename T, int N>
        inline T& Vector<T, N>::at(int index) {
            // we'll delegate the index checking to std::array
            return _data.at(index);
        }
        template<typename T, int N>
        inline const T& Vector<T, N>::at(int index) const {
            // same as previous
            return _data.at(index);
        }

        // Vector (In)Equality
        template<typename T, int N>
        inline bool operator==(const Vector<T, N>& a,
                const Vector<T, N>& b) {
            return a._data == b._data;
        }
        template<typename T, int N>
        inline bool operator!=(const Vector<T, N>& a, const Vector<T, N>& b) {
            return !(a == b);
        }

        // Vector Negation
        template<typename T, int N>
        inline Vector<T, N> operator-(const Vector<T, N>& vec) {
            Vector<T, N> ret = {};
            for (int i = 0; i < N; i++) {
                ret[i] = -vec[i];
            }
            return ret;
        }

        // Vector Scaling (Multiplication)
        template<typename T, int N>
        inline Vector<T, N> operator*(const Vector<T, N>& vec, T scale) {
            Vector<T, N> ret = vec;
            ret *= scale;
            return ret;
        }
        template<typename T, int N>
        inline Vector<T, N> operator*(T scale, const Vector<T, N>& vec) {
            return vec * scale;
        }
        template<typename T, int N>
        inline Vector<T, N>& operator*=(Vector<T, N>& vec, T scale) {
            for (int i = 0; i < N; i++) {
                vec[i] *= scale;
            }
            return vec;
        }

        // Vector Scaling (Division)
        template<typename T, int N>
        inline Vector<T, N> operator/(const Vector<T, N>& vec, T scale) {
            Vector<T, N> ret = vec;
            ret /= scale;
            return ret;
        }
        template<typename T, int N>
        inline Vector<T, N>& operator/=(Vector<T, N>& vec, T scale) {
            for (int i = 0; i < N; i++) {
                vec[i] /= scale;
            }
            return vec;
        }

        // Vector Addition
        template<typename T, int N>
        inline Vector<T, N> operator+(const Vector<T, N>& a,
                const Vector<T, N>& b) {
            Vector<T, N> ret = a;
            ret += b;
            return ret;
        }
        template<typename T, int N>
        inline Vector<T, N>& operator+=(Vector<T, N>& a,
                const Vector<T, N>& b) {
            for (int i = 0; i < N; i++) {
                a[i] += b[i];
            }
            return a;
        }
        template<typename T, int N>
        inline Vector<T, N> operator+(const Vector<T, N>& vec, T summand) {
            Vector<T, N> ret = vec;
            for (int i = 0; i < N; i++) {
                ret[i] += summand;
            }
            return ret;
        }
        template<typename T, int N>
        inline Vector<T, N> operator+(T summand, const Vector<T, N>& vec) {
            return vec + summand;
        }

        // Vector Subtraction
        template<typename T, int N>
        inline Vector<T, N> operator-(const Vector<T, N>& a,
                const Vector<T, N>& b) {
            Vector<T, N> ret = a;
            ret -= b;
            return ret;
        }
        template<typename T, int N>
        inline Vector<T, N>& operator-=(Vector<T, N>& a,
                const Vector<T, N>& b) {
            for (int i = 0; i < N; i++) {
                a[i] -= b[i];
            }
            return a;
        }
        template<typename T, int N>
        inline Vector<T, N> operator-(const Vector<T, N>& vec, T subtrahend) {
            Vector<T, N> ret = vec;
            for (int i = 0; i < N; i++) {
                ret[i] -= subtrahend;
            }
            return ret;
        }

        // Magnitude Calucaltions
        template<typename T, int N>
        inline T magnitude(const Vector<T, N>& vec) {
            return sqrt(magnitude2(vec));
        }
        template<typename T, int N>
        inline T magnitude2(const Vector<T, N>& vec) {
            return dot(vec, vec); // this is a neat little trick
        }

        // Special Products
        template<typename T, int N>
        inline T dot(const Vector<T, N>& a, const Vector<T, N>& b) {
            T ret {};
            for (int i = 0; i < N; i++) {
                ret += (a[i] * b[i]);
            }
            return ret;
        }
        template<typename T>
        inline Vector<T, 3> cross(const Vector<T, 3>& a,
                const Vector<T, 3>& b) {
            Vector<T, 3> ret {};
            ret.x(a[1] * b[2] - a[2] * b[1]);
            ret.y(a[2] * b[0] - a[0] * b[2]);
            ret.z(a[0] * b[1] - a[1] * b[0]);
            return ret;
        }

    }
}
