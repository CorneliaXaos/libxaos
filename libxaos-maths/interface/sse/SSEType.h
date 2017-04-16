#ifndef     LIBXAOS_MATHS_SSE_SSETYPE_H
#define     LIBXAOS_MATHS_SSE_SSETYPE_H

#include <cstdlib>
#include <initializer_list>
#include <type_traits>

#include "utility/cpu.h"

#ifdef LIBXAOS_FLAG_CPU_INTEL
    #include "x86intrin.h" // Pull in SSE4.2 intel intrinsics
#endif

#if defined(LIBXAOS_FLAG_DISABLE_SSE) && defined(LIBXAOS_FLAG_REQUIRE_SSE)
    static_assert(false, "Cannot DISABLE and REQUIRE SSE simultaneously!");
#endif

namespace libxaos {
    namespace sse {

        //! A useful constexpr for determining if a type can be used with SSE
        template<typename T>
        bool constexpr canUseSSE() {
            #if defined(LIBXAOS_FLAG_DISABLE_SSE)
                return false;
            #elif defined(LIBXAOS_FLAG_CPU_INTEL)
                return sizeof(T) < 16;
            #else
                return false;
            #endif
        }

        template<typename T>
        union SSEType;

    }
}

#ifndef     LIBXAOS_FLAG_DISABLE_SSE
namespace libxaos {
    namespace sse {

        // Forward declare intrinsic architecture specific options
        //! Compare Equality
        template<typename T>
        inline bool operator==(const SSEType<T>&, const SSEType<T>&);
        //! Negation
        template<typename T>
        inline SSEType<T> operator-(const SSEType<T>&);
        //! Addition
        template<typename T>
        inline SSEType<T>& operator+=(SSEType<T>&, const SSEType<T>&);
        //! Subtraction
        template<typename T>
        inline SSEType<T>& operator-=(SSEType<T>&, const SSEType<T>&);
        //! Multiplication
        template<typename T>
        inline SSEType<T>& operator*=(SSEType<T>&, const SSEType<T>&);
        //! Division
        template<typename T>
        inline SSEType<T>& operator/=(SSEType<T>&, const SSEType<T>&);
        //! Dot Product
        template<typename T>
        inline T dot(const SSEType<T>&, const SSEType<T>&);

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
                inline T& operator[](unsigned int);
                //! Gets a const element by index
                inline const T& operator[](unsigned int) const;

                //! Gets an element by index safely
                inline T& at(unsigned int);
                //! Gets a const element by index safely
                inline const T& at(unsigned int) const;

                //! The number of members bundled into this SSEType
                static constexpr const size_t MEMBER_COUNT =
                #ifdef LIBXAOS_FLAG_CPU_INTEL
                        sizeof(__m128) / sizeof(T);
                    static_assert(canUseSSE<T>(), "SSE unnecessary for type.");
                #endif

            private:
                T _data[MEMBER_COUNT];

                #ifdef LIBXAOS_FLAG_CPU_INTEL
                    // We'll only use one of the following based on T
                    __m128i _int;
                    __m128 _float;
                    __m128d _double;
                #else
                    static_assert(false,
                            "No qualifying SSE architecture detected!");
                #endif

                //! Allow the equality operator to access internals
                friend bool operator==<T>(const SSEType<T>&, const SSEType<T>&);

                //! Allow the negation operator to access internals
                friend SSEType<T> operator-<T>(const SSEType<T>&);

                //! Allow the addition operator to access internals
                friend SSEType<T>& operator+=<T>(SSEType<T>&,
                        const SSEType<T>&);

                //! Allow the subtraction operator to access internals
                friend SSEType<T>& operator-=<T>(SSEType<T>&,
                        const SSEType<T>&);

                //! Allow the multiplication operator to access internals
                friend SSEType<T>& operator*=<T>(SSEType<T>&,
                        const SSEType<T>&);

                //! Allow the division operator to access internals
                friend SSEType<T>& operator/=<T>(SSEType<T>&,
                        const SSEType<T>&);

                //! Allow the dot product function to access internals
                friend T dot<T>(const SSEType<T>&, const SSEType<T>&);
        };

        // Architecture agnostic
        //! Compare Inequality
        template<typename T>
        inline bool operator!=(const SSEType<T>&, const SSEType<T>&);
        //! Addition
        template<typename T>
        inline SSEType<T> operator+(const SSEType<T>&, const SSEType<T>&);
        //! Subtraction
        template<typename T>
        inline SSEType<T> operator-(const SSEType<T>&, const SSEType<T>&);
        //! Multiplication
        template<typename T>
        inline SSEType<T> operator*(const SSEType<T>&, const SSEType<T>&);
        //! Division
        template<typename T>
        inline SSEType<T> operator/(const SSEType<T>&, const SSEType<T>&);

    }
}

// Include common implementations
#include "SSEType-tpp.h"

#ifdef LIBXAOS_FLAG_CPU_INTEL
    #include "__internal__/intel/SSEType-tpp.h"
#endif

#endif   // LIBXAOS_FLAG_DISABLE_SSE

#endif   // LIBXAOS_MATHS_SSE_SSETYPE_H
