/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_EXPR_F_MUL_H
#define LIBSIMDPP_SIMDPP_DETAIL_EXPR_F_MUL_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON
    #include <simdpp/detail/null/math.h>
#endif

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {

template<class R, class E1, class E2> SIMDPP_INL
float32<4> expr_eval_mul(const float32<4,E1>& qa,
                         const float32<4,E2>& qb)
{
    float32<4> a = qa.eval();
    float32<4> b = qb.eval();
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_NO_FLT_SP
    return detail::null::mul(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_mul_ps(a,b);
#elif SIMDPP_USE_NEON_FLT_SP
    return vmulq_f32(a, b);
#elif SIMDPP_USE_VSX_206
    return vec_mul((__vector float) a, (__vector float) b);
#elif SIMDPP_USE_ALTIVEC
    return vec_madd((__vector float)a, (__vector float)b,
                    (__vector float)(float32x4) make_zero());
#elif SIMDPP_USE_MSA
    return __msa_fmul_w(a, b);
#endif
}

#if SIMDPP_USE_AVX
template<class R, class E1, class E2> SIMDPP_INL
float32<8> expr_eval_mul(const float32<8,E1>& qa,
                         const float32<8,E2>& qb)
{
    float32<8> a = qa.eval();
    float32<8> b = qb.eval();
    return _mm256_mul_ps(a, b);
}
#endif

#if SIMDPP_USE_AVX512F
template<class R, class E1, class E2> SIMDPP_INL
float32<16> expr_eval_mul(const float32<16,E1>& qa,
                          const float32<16,E2>& qb)
{
    float32<16> a = qa.eval();
    float32<16> b = qb.eval();
    return _mm512_mul_ps(a, b);
}
#endif

template<class R, unsigned N, class E1, class E2> SIMDPP_INL
float32<N> expr_eval_mul(const float32<N,E1>& qa,
                         const float32<N,E2>& qb)
{
    float32<N> a = qa.eval();
    float32<N> b = qb.eval();
    SIMDPP_VEC_ARRAY_IMPL2(float32<N>, mul, a, b);
}

// -----------------------------------------------------------------------------

template<class R, class E1, class E2> SIMDPP_INL
float64<2> expr_eval_mul(const float64<2,E1>& qa,
                         const float64<2,E2>& qb)
{
    float64<2> a = qa.eval();
    float64<2> b = qb.eval();
#if SIMDPP_USE_SSE2
    return _mm_mul_pd(a, b);
#elif SIMDPP_USE_NEON64
    return vmulq_f64(a, b);
#elif SIMDPP_USE_VSX_206
    return vec_mul((__vector double) a, (__vector double) b);
#elif SIMDPP_USE_MSA
    return __msa_fmul_d(a, b);
#elif SIMDPP_USE_NULL || SIMDPP_USE_NEON32 || SIMDPP_USE_ALTIVEC
    return detail::null::mul(a, b);
#endif
}

#if SIMDPP_USE_AVX
template<class R, class E1, class E2> SIMDPP_INL
float64<4> expr_eval_mul(const float64<4,E1>& qa,
                         const float64<4,E2>& qb)
{
    float64<4> a = qa.eval();
    float64<4> b = qb.eval();
    return _mm256_mul_pd(a, b);
}
#endif

#if SIMDPP_USE_AVX512F
template<class R, class E1, class E2> SIMDPP_INL
float64<8> expr_eval_mul(const float64<8,E1>& qa,
                         const float64<8,E2>& qb)
{
    float64<8> a = qa.eval();
    float64<8> b = qb.eval();
    return _mm512_mul_pd(a, b);
}
#endif

template<class R, unsigned N, class E1, class E2> SIMDPP_INL
float64<N> expr_eval_mul(const float64<N,E1>& qa,
                         const float64<N,E2>& qb)
{
    float64<N> a = qa.eval();
    float64<N> b = qb.eval();
    SIMDPP_VEC_ARRAY_IMPL2(float64<N>, mul, a, b);
}

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

