/**
 *  @file SSETypeFloating-tpp.h
 *  @brief Intel specific implementations for floating SSETypes
 */

namespace libxaos {
    namespace sse {
        namespace internal {
            namespace intel {
                namespace floating {

                    template<typename T>
                    union HelperPD {
                        public:
                            T _data[2];
                            __m128d _double;
                    };
                    template<typename T>
                    union HelperPS {
                        public:
                            T _data[4];
                            __m128 _float;
                    };

                    // equals
                    template<typename T>
                    inline EnableIf<sizeof(T) == 8, bool> equals(CRefs& a,
                            CRefs& b) {
                        __m128i result =
                                reinterpret_cast<__m128i>(
                                _mm_cmpneq_pd(a._double, b._double));
                        uint16_t eval = _mm_movemask_epi8(result);
                        return eval == uint16_t{0};
                    }
                    template<typename T>
                    inline EnableIf<sizeof(T) == 4, bool> equals(CRefs& a,
                            CRefs& b) {
                        __m128i result =
                                reinterpret_cast<__m128i>(
                                _mm_cmpneq_ps(a._float, b._float));
                        uint16_t eval = _mm_movemask_epi8(result);
                        return eval == uint16_t{0};
                    }

                    // negate
                    template<typename T>
                    inline EnableIf<sizeof(T) == 8, void> negate(Refs& a,
                            CRefs& b) {
                        __m128d zeroes = _mm_set_pd(0, 0);
                        a._double = _mm_sub_pd(zeroes, b._double);
                    }
                    template<typename T>
                    inline EnableIf<sizeof(T) == 4, void> negate(Refs& a,
                            CRefs& b) {
                        __m128 zeroes = _mm_set_ps(0, 0, 0, 0);
                        a._float = _mm_sub_ps(zeroes, b._float);
                    }

                    // add
                    template<typename T>
                    inline EnableIf<sizeof(T) == 8, void> add(Refs& a,
                            CRefs& b) {
                        a._double = _mm_add_pd(a._double, b._double);
                    }
                    template<typename T>
                    inline EnableIf<sizeof(T) == 4, void> add(Refs& a,
                            CRefs& b) {
                        a._float = _mm_add_ps(a._float, b._float);
                    }

                    // subtract
                    template<typename T>
                    inline EnableIf<sizeof(T) == 8, void> subtract(Refs& a,
                            CRefs& b) {
                        a._double = _mm_sub_pd(a._double, b._double);
                    }
                    template<typename T>
                    inline EnableIf<sizeof(T) == 4, void> subtract(Refs& a,
                            CRefs& b) {
                        a._float = _mm_sub_ps(a._float, b._float);
                    }

                    // multiply
                    template<typename T>
                    inline EnableIf<sizeof(T) == 8, void> multiply(Refs& a,
                            CRefs& b) {
                        a._double = _mm_mul_pd(a._double, b._double);
                    }
                    template<typename T>
                    inline EnableIf<sizeof(T) == 4, void> multiply(Refs& a,
                            CRefs& b) {
                        a._float = _mm_mul_ps(a._float, b._float);
                    }

                    // divide
                    template<typename T>
                    inline EnableIf<sizeof(T) == 8, void> divide(Refs& a,
                            CRefs& b) {
                        a._double = _mm_div_pd(a._double, b._double);
                    }
                    template<typename T>
                    inline EnableIf<sizeof(T) == 4, void> divide(Refs& a,
                            CRefs& b) {
                        a._float = _mm_div_ps(a._float, b._float);
                    }

                    // dot
                    template<typename T>
                    inline EnableIf<sizeof(T) == 8, T> dot(CRefs& a,
                            CRefs& b) {
                        __m128d result = _mm_dp_pd(a._double, b._double, 0x31);
                        HelperPD<T> helper {};
                        helper._double = result;
                        return static_cast<T>(helper._data[0]);
                    }
                    template<typename T>
                    inline EnableIf<sizeof(T) == 4, T> dot(CRefs& a,
                            CRefs& b) {
                        __m128 result = _mm_dp_ps(a._float, b._float, 0xF1);
                        HelperPS<T> helper {};
                        helper._float = result;
                        return static_cast<T>(helper._data[0]);
                    }

                }
            }
        }
    }
}
