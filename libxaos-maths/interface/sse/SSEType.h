#ifndef     LIBXAOS_MATHS_SSE_SSETYPE_H
#define     LIBXAOS_MATHS_SSE_SSETYPE_H

#include <cstdlib>
#include <initializer_list>
#include <type_traits>

#include "utility/cpu.h"

#ifdef LIBXAOS_FLAG_CPU_INTEL
    #include "emmintrin.h" // Pull in SSE2 intel intrinsics
#endif

#if defined(LIBXAOS_FLAG_DISABLE_SSE) && defined(LIBXAOS_FLAG_REQUIRE_SSE)
    static_assert(false, "Cannot DISABLE and REQUIRE SSE simultaneously!");
#endif

#ifndef     LIBXAOS_FLAG_DISABLE_SSE
namespace libxaos {
    namespace sse {

        /**
         *  @brief A wrapper around the "sse" types provided by different cpus.
         *
         *  This class wrappers the Streaming SIMD Extension types provided by
         *  various CPUs in such a way that one does not need to concern
         *  oneself with which particular cpu the code is being compiled for.
         *
         *  This header is designed in such a way that one may include it
         *  EVEN IF LIBXAOS_FLAG_DISABLE_SSE is declared.  The onus of ensuring
         *  that the SSEType is referred to indirectly is up to the user of the
         *  class.  (I.e. check to make sure LIBXAOS_FLAG_DISABLE_SSE isn't
         *  declared before using SSEType.)
         */
        template<typename T>
        union SSEType {
            static_assert(std::is_arithmetic<T>::value,
                "The SSEType can only be used with arithmetic types!");

            public:

                //! Instantiates an SSEType with default values
                SSEType();
                //! Instantiates an SSEType using a single scalar
                explicit SSEType(T);
                //! Instantiates an SSEType using the provided values
                explicit SSEType(std::initializer_list<T>);
                ~SSEType() = default;

                SSEType(const SSEType<T>&);
                SSEType<T>& operator=(const SSEType<T>&);
                SSEType(SSEType<T>&&);
                SSEType<T>& operator=(SSEType<T>&&);

                //! Gets an element by index
                T& operator[](unsigned int);
                //! Gets a const element by index
                const T& operator[](unsigned int) const;

                //! Gets an element by index safely
                T& at(unsigned int);
                //! Gets a const element by index safely
                const T& at(unsigned int) const;

                //! Compares two SSETypes for equality
                bool operator==(const SSEType<T>&);
                //! Compares two SSETypes for inequality
                bool operator!=(const SSEType<T>&);

                #ifdef LIBXAOS_FLAG_CPU_INTEL
                    static_assert(sizeof(T) < 16, "SSE unnecessary for type.");
                    //! The number of members bundled into this SSEType
                    static constexpr const size_t BUNDLED_MEMBERS =
                            16 / sizeof(T); // 16 bytes divided by sizeof(T)
                #endif

            private:
                #ifdef LIBXAOS_FLAG_CPU_INTEL
                    T _data[BUNDLED_MEMBERS];

                    // We'll only use one of the following based on T
                    __m128 _float;
                    __m128i _int;
                    __m128d _double;
                #else
                    static_assert(false,
                            "No qualifying SSE architecture detected!");
                #endif

                //! Allow the equality operator to access internals
                template<typename S>
                friend bool operator==(const SSEType<S>&, const SSEType<S>&);

                //! Allow the negation operator to access internals
                template<typename S>
                friend SSEType<S> operator-(const SSEType<S>&);

                //! Allow the addition operator to access internals
                template<typename S>
                friend SSEType<S>& operator+=(SSEType<S>&, const SSEType<S>&);

                //! Allow the subtraction operator to access internals
                template<typename S>
                friend SSEType<S>& operator-=(SSEType<S>&, const SSEType<S>&);

                //! Allow the multiplication operator to access internals
                template<typename S>
                friend SSEType<S>& operator*=(SSEType<S>&, const SSEType<S>&);

                //! Allow the division operator to access internals
                template<typename S>
                friend SSEType<S>& operator/=(SSEType<S>&, const SSEType<S>&);

                //! Allow the dot product function to access internals
                template<typename S>
                friend T dot(const SSEType<S>&, const SSEType<S>&);
        };

        //! Compare Equality
        template<typename T>
        inline bool operator==(const SSEType<T>&, const SSEType<T>&);
        //! Compare Inequality
        template<typename T>
        inline bool operator!=(const SSEType<T>&, const SSEType<T>&);

        //! Negation
        template<typename T>
        inline SSEType<T> operator-(const SSEType<T>&);

        //! Addition
        template<typename T>
        inline SSEType<T> operator+(const SSEType<T>&, const SSEType<T>&);
        template<typename T>
        inline SSEType<T>& operator+=(SSEType<T>&, const SSEType<T>&);

        //! Subtraction
        template<typename T>
        inline SSEType<T> operator-(const SSEType<T>&, const SSEType<T>&);
        template<typename T>
        inline SSEType<T>& operator-=(SSEType<T>&, const SSEType<T>&);

        //! Multiplication
        template<typename T>
        inline SSEType<T> operator*(const SSEType<T>&, const SSEType<T>&);
        template<typename T>
        inline SSEType<T>& operator*=(SSEType<T>&, const SSEType<T>&);

        //! Division
        template<typename T>
        inline SSEType<T> operator/(const SSEType<T>&, const SSEType<T>&);
        template<typename T>
        inline SSEType<T>& operator/=(SSEType<T>&, const SSEType<T>&);

        //! Dot Product
        template<typename T>
        inline T dot(const SSEType<T>&, const SSEType<T>&);
    }
}

// Include common implementations
#include "SSEType-tpp.h"

#ifdef LIBXAOS_FLAG_CPU_INTEL
    #include "intel/SSEType-ttp.h"
#endif

#endif   // LIBXAOS_FLAG_DISABLE_SSE

#endif   // LIBXAOS_MATHS_SSE_SSETYPE_H
