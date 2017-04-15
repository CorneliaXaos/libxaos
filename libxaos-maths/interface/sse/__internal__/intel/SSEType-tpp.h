/**
 *  @file SSEType-tpp.H
 *  @brief Intel specific implementations for SSEType.
 */

#include <cstdint>

namespace libxaos {
    namespace sse {

        namespace {
            template<bool B, typename T>
            using EnableIf = typename std::enable_if<B, T>::type;

            template<typename T>
            constexpr bool IsFloating() {
                return std::is_floating_point<T>::value;
            }

            template<typename T>
            constexpr bool IsIntegral() {
                return std::is_integral<T>::value;
            }
        }

        // Hopefully this deters outside use.
        namespace internal {
            namespace intel {

                //! Used for passing internals to helper functions
                //! Basically exposes the internals of SSEType to delegates
                struct CRefs {
                    CRefs(const __m128i& intRef, const __m128& floatRef,
                        const __m128d& doubleRef) :
                        _int(intRef), _float(floatRef), _double(doubleRef) {}

                    const __m128i& _int;
                    const __m128& _float;
                    const __m128d& _double;
                };
                struct Refs {
                    Refs(__m128i& intRef, __m128& floatRef,
                            __m128d& doubleRef) : _int(intRef),
                            _float(floatRef), _double(doubleRef) {}

                    __m128i& _int;
                    __m128& _float;
                    __m128d& _double;
                };

                // These forward declares will WRITE TO the first argument if
                // they return void.  Basically, they implement the opeartions
                // for +=, -=, *=, and /= .  The exception is operator- (unary)
                // which is passed a second refs object it writes to (since the
                // first is const essentially)

                //// Integral Forward Declares
                namespace integral {

                    template<typename T>
                    inline EnableIf<sizeof(T) == 8, bool> equals(CRefs&,
                            CRefs&);
                    template<typename T>
                    inline EnableIf<sizeof(T) == 4, bool> equals(CRefs&,
                            CRefs&);
                    template<typename T>
                    inline EnableIf<sizeof(T) == 2, bool> equals(CRefs&,
                            CRefs&);
                    template<typename T>
                    inline EnableIf<sizeof(T) == 1, bool> equals(CRefs&,
                            CRefs&);

                    template<typename T>
                    inline EnableIf<sizeof(T) == 8, void> negate(Refs&, CRefs&);
                    template<typename T>
                    inline EnableIf<sizeof(T) == 4, void> negate(Refs&, CRefs&);
                    template<typename T>
                    inline EnableIf<sizeof(T) == 2, void> negate(Refs&, CRefs&);
                    template<typename T>
                    inline EnableIf<sizeof(T) == 1, void> negate(Refs&, CRefs&);

                    template<typename T>
                    inline EnableIf<sizeof(T) == 8, void> add(Refs&, CRefs&);
                    template<typename T>
                    inline EnableIf<sizeof(T) == 4, void> add(Refs&, CRefs&);
                    template<typename T>
                    inline EnableIf<sizeof(T) == 2, void> add(Refs&, CRefs&);
                    template<typename T>
                    inline EnableIf<sizeof(T) == 1, void> add(Refs&, CRefs&);

                    template<typename T>
                    inline EnableIf<sizeof(T) == 8, void> subtract(Refs&,
                            CRefs&);
                    template<typename T>
                    inline EnableIf<sizeof(T) == 4, void> subtract(Refs&,
                            CRefs&);
                    template<typename T>
                    inline EnableIf<sizeof(T) == 2, void> subtract(Refs&,
                            CRefs&);
                    template<typename T>
                    inline EnableIf<sizeof(T) == 1, void> subtract(Refs&,
                            CRefs&);

                    template<typename T>
                    inline EnableIf<sizeof(T) == 8, void> multiply(Refs&,
                            CRefs&);
                    template<typename T>
                    inline EnableIf<sizeof(T) == 4, void> multiply(Refs&,
                            CRefs&);
                    template<typename T>
                    inline EnableIf<sizeof(T) == 2, void> multiply(Refs&,
                            CRefs&);
                    template<typename T>
                    inline EnableIf<sizeof(T) == 1, void> multiply(Refs&,
                            CRefs&);

                    template<typename T>
                    inline void divide(Refs&, CRefs&);

                    template<typename T>
                    inline T dot(CRefs&, CRefs&);

                }

                //// Floating Forward Declares
                namespace floating {

                    template<typename T>
                    inline EnableIf<sizeof(T) == 8, bool> equals(CRefs&,
                            CRefs&);
                    template<typename T>
                    inline EnableIf<sizeof(T) == 4, bool> equals(CRefs&,
                            CRefs&);

                    template<typename T>
                    inline EnableIf<sizeof(T) == 8, void> negate(Refs&, CRefs&);
                    template<typename T>
                    inline EnableIf<sizeof(T) == 4, void> negate(Refs&, CRefs&);

                    template<typename T>
                    inline EnableIf<sizeof(T) == 8, void> add(Refs&, CRefs&);
                    template<typename T>
                    inline EnableIf<sizeof(T) == 4, void> add(Refs&, CRefs&);

                    template<typename T>
                    inline EnableIf<sizeof(T) == 8, void> subtract(Refs&,
                            CRefs&);
                    template<typename T>
                    inline EnableIf<sizeof(T) == 4, void> subtract(Refs&,
                            CRefs&);

                    template<typename T>
                    inline EnableIf<sizeof(T) == 8, void> multiply(Refs&,
                            CRefs&);
                    template<typename T>
                    inline EnableIf<sizeof(T) == 4, void> multiply(Refs&,
                            CRefs&);

                    template<typename T>
                    inline EnableIf<sizeof(T) == 8, void> divide(Refs&, CRefs&);
                    template<typename T>
                    inline EnableIf<sizeof(T) == 4, void> divide(Refs&, CRefs&);

                    template<typename T>
                    inline EnableIf<sizeof(T) == 8, T> dot(CRefs&, CRefs&);
                    template<typename T>
                    inline EnableIf<sizeof(T) == 4, T> dot(CRefs&, CRefs&);

                }
            }
        }

        //// Implement SSEType functions
        // operator==
        template<typename T>
        inline bool operator==(const SSEType<T>& a, const SSEType<T>& b) {
            internal::intel::CRefs refsA {a._int, a._float, a._double};
            internal::intel::CRefs refsB {b._int, b._float, b._double};

            bool ret {};
            if (IsIntegral<T>()) {
                ret = internal::intel::integral::equals<T>(refsA, refsB);
            } else if (IsFloating<T>()) {
                ret = internal::intel::floating::equals<T>(refsA, refsB);
            }

            return ret;
        }

        // operator- (unary)
        template<typename T>
        inline SSEType<T> operator-(const SSEType<T>& a) {
            SSEType<T> ret {};
            internal::intel::Refs refsRet {ret._int, ret._float, ret._double};
            internal::intel::CRefs refsA {a._int, a._float, a._double};

            if (IsIntegral<T>()) {
                internal::intel::integral::negate<T>(refsRet, refsA);
            } else if (IsFloating<T>()) {
                internal::intel::floating::negate<T>(refsRet, refsA);
            }

            return ret;
        }

        // operator+=
        template<typename T>
        inline SSEType<T>& operator+=(SSEType<T>& a, const SSEType<T>& b) {
            internal::intel::Refs refsA {a._int, a._float, a._double};
            internal::intel::CRefs refsB {b._int, b._float, b._double};

            if (IsIntegral<T>()) {
                internal::intel::integral::add<T>(refsA, refsB);
            } else if (IsFloating<T>()) {
                internal::intel::floating::add<T>(refsA, refsB);
            }

            return a;
        }

        // operator-=
        template<typename T>
        inline SSEType<T>& operator-=(SSEType<T>& a, const SSEType<T>& b) {
            internal::intel::Refs refsA {a._int, a._float, a._double};
            internal::intel::CRefs refsB {b._int, b._float, b._double};

            if (IsIntegral<T>()) {
                internal::intel::integral::subtract<T>(refsA, refsB);
            } else if (IsFloating<T>()) {
                internal::intel::floating::subtract<T>(refsA, refsB);
            }

            return a;
        }

        // operator*=
        template<typename T>
        inline SSEType<T>& operator*=(SSEType<T>& a, const SSEType<T>& b) {
            internal::intel::Refs refsA {a._int, a._float, a._double};
            internal::intel::CRefs refsB {b._int, b._float, b._double};

            if (IsIntegral<T>()) {
                internal::intel::integral::multiply<T>(refsA, refsB);
            } else if (IsFloating<T>()) {
                internal::intel::floating::multiply<T>(refsA, refsB);
            }

            return a;
        }

        // operator/=
        template<typename T>
        inline SSEType<T>& operator/=(SSEType<T>& a, const SSEType<T>& b) {
            internal::intel::Refs refsA {a._int, a._float, a._double};
            internal::intel::CRefs refsB {b._int, b._float, b._double};

            if (IsIntegral<T>()) {
                internal::intel::integral::divide<T>(refsA, refsB);
            } else if (IsFloating<T>()) {
                internal::intel::floating::divide<T>(refsA, refsB);
            }

            return a;
        }

        // dot
        template<typename T>
        inline T dot(const SSEType<T>& a, const SSEType<T>& b) {
            internal::intel::CRefs refsA {a._int, a._float, a._double};
            internal::intel::CRefs refsB {b._int, b._float, b._double};

            T ret {};
            if (IsIntegral<T>()) {
                ret = internal::intel::integral::dot<T>(refsA, refsB);
            } else if (IsFloating<T>()) {
                ret = internal::intel::floating::dot<T>(refsA, refsB);
            }

            return ret;
        }
    }
}

// Bring in the implementations for the internal namespace
#include "SSETypeIntegral-tpp.h"
#include "SSETypeFloating-tpp.h"
