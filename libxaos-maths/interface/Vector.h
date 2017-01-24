#ifndef     LIBXAOS_MATHS_VECTOR_H
#define     LIBXAOS_MATHS_VECTOR_H

#include <array>
#include <initializer_list>
#include <type_traits>

namespace libxaos {
    namespace maths {

        namespace {
            template<typename T>
            using IsArithmetic = std::is_arithmetic<T>::value;

            template<bool B, typename T>
            using EnableIf = typename std::enable_if<B, T>::type;

            constexpr bool HasIndex(int n, int index) {
                return index < n;
            }
        }

        /**
         *  @brief This class represents an N length Vector of type T.
         *
         *  This class is a customizable, N-length array of numeric units of
         *  type T.  It can be used to represent useful concepts such as points
         *  and displacements.  It should be noted that no effort is made by the
         *  implementation to preserve precision in certain cases.
         *  (i.e. dividing two integers will always yield integral results)
         *
         *  @tparam T the numeric type of the objects contained in the Vector.
         *  @tparam N the integral length of the Vector.
         */
        template<typename T, int N>
        class Vector {
            static_assert(IsArithmetic<T>, "Vectors must be arithmetic!");

            public:
                Vector();
                //! Initializes the Vector from a List.
                Vector(std::initializer_list<T>);
                ~Vector();

                Vector(const Vector<T, N>&);
                Vector<T, N>& operator=(const Vector<T, N>&);
                Vector(Vector<T,N>&&);
                Vector<T, N>& operator=(Vector<T, N>&&);

                //! Accesses the first (x) element of the Vector.
                template<int M = N>
                inline EnableIf<HasIndex(M, 0), T> x() const;
                //! Sets the first (x) element of the Vector.
                template<int M = N>
                inline EnableIF<HasIndex(M, 0), void> x(T);

                //! Accesses the second (y) element of the Vector.
                template<int M = N>
                inline EnableIf<HasIndex(M, 1), T> y() const;
                //! Sets the second (y) element of the Vector.
                template<int M = N>
                inline EnableIF<HasIndex(M, 1), void> y(T);

                //! Accesses the third (z) element of the Vector.
                template<int M = N>
                inline EnableIf<HasIndex(M, 2), T> z() const;
                //! Sets the third (z) element of the Vector.
                template<int M = N>
                inline EnableIF<HasIndex(M, 2), void> z(T);

                //! Accesses/Sets the Nth element of the Vector.
                inline T& operator[](int);
                //! Accesses the Nth element of the Vector.
                inline const T& operator[](int) const;

                //! Safely accesses/sets the Nth element of the Vector.
                inline T& at(int);
                //! Safely accesses the Nth element of the Vector.
                inline const T& at(int) const;

                //! The size of this Vector.
                static constexpr const int SIZE = N;

            private:
                //! The internal data held within this Vector.
                std::array<T, N> _data;
        };

        //! Checks Vector Equality
        template<typename T, int N>
        inline bool operator==(const Vector<T, N>&, const Vector<T, N>&);
        //! Checks Vector Inequality
        template<typename T, int N>
        inline bool operator!=(const Vector<T, N>&, const Vector<T, N>&);

        //! Negates a Vector
        template<typename T, int N>
        inline Vector<T, N> operator-(const Vector<T, N>&);

        //! Scales (multiplication) and returns a new Vector.
        template<typename T, int N>
        inline Vector<T, N> operator*(const Vector<T, N>&, T);
        //! Scales (multiplication) and returns a new Vector.
        template<typename T, int N>
        inline Vector<T, N> operator*(T, const Vector<T, N>&);
        //! Scales (multiplication) the argument Vector.
        template<typename T, int N>
        inline Vector<T, N> operator*=(Vector<T, N>&, T);

        //! Scales (division) and returns a new Vector.
        template<typename T, int N>
        inline Vector<T, N> operator/(const Vector<T, N>&, T);
        //! Scales (division) the argument Vector.
        template<typename T, int N>
        inline Vector<T, N> operator/=(Vector<T, N>&, T);

        //! Sums and returns a new Vector.
        template<typename T, int N>
        inline Vector<T, N> operator+(const Vector<T, N>&, const Vector<T, N>&);
        //! Sums the argument vectors and stores the result in the first.
        template<typename T, int N>
        inline Vector<T, N> operator+=(Vector<T,N>&, const Vector<T, N>&);

        //! Differences and returns a new Vector.
        template<typename T, int N>
        inline Vector<T, N> operator-(const Vector<T, N>&, const Vector<T, N>&);
        //! Differences the argument vectors and stores the result in the first.
        template<typename T, int N>
        inline Vector<T, N> operator-=(Vector<T,N>&, const Vector<T, N>&);

        //! Calculates the Magnitude of a Vector.
        template<typename T, int N>
        inline T magnitude(const Vector<T, N>&);
        //! Calculates teh Magnitude squared of a Vector.
        template<typename T, int N>
        inline T magnitude2(const Vector<T, N>&);

        //! Calculates the Dot Product of two Vectors.
        template<typename T, int N>
        inline T dot(const Vector<T, N>&, const Vector<T, N>&);
        //! Calculates the Cross Product of two Vectors (only valid for N == 3).
        template<typename T, int N>
        inline T cross(const Vector<T, N>&, const Vector<T, N>&);
    }
}

#endif   // LIBXAOS_MATHS_VECTOR_H
