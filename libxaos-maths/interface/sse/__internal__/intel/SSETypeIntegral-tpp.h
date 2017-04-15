/**
 *  @file SSETypeIntegral-tpp.h
 *  @brief Intel specific implementations for integral SSETypes
 */

namespace libxaos {
    namespace sse {
        namespace internal {
            namespace intel {
                namespace integral {

                    template<typename T, unsigned int COUNT>
                    union Helper {
                        public:
                            T _data[COUNT];
                            __m128i _int;
                    };

                    // equals
                    template<typename T>
                    inline EnableIf<sizeof(T) == 8, bool> equals(CRefs& a,
                            CRefs& b) {
                        __m128i result = _mm_cmpeq_epi64(a._int, b._int);
                        uint16_t eval = _mm_movemask_epi8(result);
                        return eval == uint16_t{0xFFFF};
                    }
                    template<typename T>
                    inline EnableIf<sizeof(T) == 4, bool> equals(CRefs& a,
                            CRefs& b) {
                        __m128i result = _mm_cmpeq_epi32(a._int, b._int);
                        uint16_t eval = _mm_movemask_epi8(result);
                        return eval == uint16_t{0xFFFF};
                    }
                    template<typename T>
                    inline EnableIf<sizeof(T) == 2, bool> equals(CRefs& a,
                            CRefs& b) {
                        __m128i result = _mm_cmpeq_epi16(a._int, b._int);
                        uint16_t eval = _mm_movemask_epi8(result);
                        return eval == uint16_t{0xFFFF};
                    }
                    template<typename T>
                    inline EnableIf<sizeof(T) == 1, bool> equals(CRefs& a,
                            CRefs& b) {
                        __m128i result = _mm_cmpeq_epi8(a._int, b._int);
                        uint16_t eval = _mm_movemask_epi8(result);
                        return eval == uint16_t{0xFFFF};
                    }

                    // negate
                    template<typename T>
                    inline EnableIf<sizeof(T) == 8, void> negate(Refs& a,
                            CRefs& b) {
                        __m128i zero = _mm_set_epi64x(0, 0);
                        a._int = _mm_sub_epi64(zero, b._int);
                    }
                    template<typename T>
                    inline EnableIf<sizeof(T) == 4, void> negate(Refs& a,
                            CRefs& b) {
                        __m128i zero = _mm_set_epi32(0, 0, 0, 0);
                        a._int = _mm_sub_epi32(zero, b._int);
                    }
                    template<typename T>
                    inline EnableIf<sizeof(T) == 2, void> negate(Refs& a,
                            CRefs& b) {
                        __m128i zero = _mm_set_epi16(0, 0, 0, 0, 0, 0, 0, 0);
                        a._int = _mm_sub_epi16(zero, b._int);
                    }
                    template<typename T>
                    inline EnableIf<sizeof(T) == 1, void> negate(Refs& a,
                            CRefs& b) {
                        __m128i zero = _mm_set_epi8(0, 0, 0, 0, 0, 0, 0, 0,
                                                    0, 0, 0, 0, 0, 0, 0, 0);
                        a._int = _mm_sub_epi8(zero, b._int);
                    }

                    // add
                    template<typename T>
                    inline EnableIf<sizeof(T) == 8, void> add(Refs& a,
                            CRefs& b) {
                        a._int = _mm_add_epi64(a._int, b._int);
                    }
                    template<typename T>
                    inline EnableIf<sizeof(T) == 4, void> add(Refs& a,
                            CRefs& b) {
                        a._int = _mm_add_epi32(a._int, b._int);
                    }
                    template<typename T>
                    inline EnableIf<sizeof(T) == 2, void> add(Refs& a,
                            CRefs& b) {
                        a._int = _mm_add_epi16(a._int, b._int);
                    }
                    template<typename T>
                    inline EnableIf<sizeof(T) == 1, void> add(Refs& a,
                            CRefs& b) {
                        a._int = _mm_add_epi8(a._int, b._int);
                    }

                    // subtract
                    template<typename T>
                    inline EnableIf<sizeof(T) == 8, void> subtract(Refs& a,
                            CRefs& b) {
                        a._int = _mm_sub_epi64(a._int, b._int);
                    }
                    template<typename T>
                    inline EnableIf<sizeof(T) == 4, void> subtract(Refs& a,
                            CRefs& b) {
                        a._int = _mm_sub_epi32(a._int, b._int);
                    }
                    template<typename T>
                    inline EnableIf<sizeof(T) == 2, void> subtract(Refs& a,
                            CRefs& b) {
                        a._int = _mm_sub_epi16(a._int, b._int);
                    }
                    template<typename T>
                    inline EnableIf<sizeof(T) == 1, void> subtract(Refs& a,
                            CRefs& b) {
                        a._int = _mm_sub_epi8(a._int, b._int);
                    }

                    // multiply
                    template<typename T>
                    inline EnableIf<sizeof(T) == 8, void> multiply(Refs& a,
                            CRefs& b) {
                        // no performance boost from SSE!!!
                        Helper<T, 2U> helperA {}, helperB {};
                        helperA._int = a._int;
                        helperB._int = b._int;

                        for (unsigned int i = 0U; i < 2U; i++) {
                            helperA._data[i] *= helperB._data[i];
                        }
                        a._int = helperA._int;
                    }
                    template<typename T>
                    inline EnableIf<sizeof(T) == 4, void> multiply(Refs& a,
                            CRefs& b) {
                        a._int = _mm_mullo_epi32(a._int, b._int);
                    }
                    template<typename T>
                    inline EnableIf<sizeof(T) == 2, void> multiply(Refs& a,
                            CRefs& b) {
                        a._int = _mm_mullo_epi16(a._int, b._int);
                    }
                    template<typename T>
                    inline EnableIf<sizeof(T) == 1, void> multiply(Refs& a,
                            CRefs& b) {
                        // no performance boost from SSE!!!
                        Helper<T, 16U> helperA {}, helperB {};
                        helperA._int = a._int;
                        helperB._int = b._int;

                        for (unsigned int i = 0U; i < 16U; i++) {
                            helperA._data[i] *= helperB._data[i];
                        }
                        a._int = helperA._int;
                    }

                    // divide
                    // no performance boost from SSE!!!
                    template<typename T>
                    inline void divide(Refs& a, CRefs& b) {
                        Helper<T, sizeof(__m128i) / sizeof(T)> helperA {},
                                helperB {};
                        helperA._int = a._int;
                        helperB._int = b._int;

                        for (unsigned int i = 0U; i <
                                sizeof(__m128i) / sizeof(T); i++) {
                            helperA._data[i] /= helperB._data[i];
                        }
                        a._int = helperA._int;
                    }

                    // dot
                    // minor SSE performance boost
                    template<typename T>
                    inline T dot(CRefs& a, CRefs& b) { // this code got ugly..
                        __m128i tempInt = a._int;
                        __m128 tempFloat = a._float;
                        __m128d tempDouble = a._double;
                        Refs temp {tempInt, tempFloat, tempDouble};

                        multiply<T>(temp, b);
                        Helper<T, sizeof(__m128i) / sizeof(T)> helper {};
                        helper._int = temp._int;

                        T ret = T{0};
                        for (unsigned int i = 0U; i <
                                sizeof(__m128i) / sizeof(T); i++) {
                            ret += static_cast<T>(helper._data[i]);
                        }
                        return ret;
                    }
                }
            }
        }
    }
}
