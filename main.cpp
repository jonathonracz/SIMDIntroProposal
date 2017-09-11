#include <iostream>
#include <chrono>
#include <vector>

#include "SIMDFuncsNone.h"

#ifdef ENABLE_SSE
#include "SIMDFuncsSSE.h"
#endif

#ifdef ENABLE_AVX
#include "SIMDFuncsAVX.h"
#endif

#ifdef ENABLE_NEON
#include "SIMDFuncsNEON.h"
#endif

static 

static inline void benchmark_multiply(void (*impl)(float*, size_t, float))
{
    std::cout << __PRETTY_FUNCTION__ << "\n";

    float multiplier = 0.5f;
    std::vector<float> buffer;

    for (size_t i = 256; i <= std::pow(); i *= 2)
    {
        buffer.clear();
        buffer.resize(i, 0.5f);

        auto start = std::chrono::steady_clock::now();
        (*impl)(buffer.data(), buffer.size(), multiplier);
        auto end = std::chrono::steady_clock::now();

        std::cout << i << " samples: " << std::chrono::duration<float, std::micro>(end - start).count() << " μs\n";
    }

    std::cout << "\n";
}

int main(int argc, char** argv)
{
    benchmark_multiply(none::multiply);

    #ifdef ENABLE_SSE
    benchmark_multiply(sse::multiply);
    // Zero all SIMD registers to negate the AVX<->SSE transition penalty. See
    // https://software.intel.com/en-us/articles/avoiding-avx-sse-transition-penalties
    _mm256_zeroall();
    #endif

    #ifdef ENABLE_AVX
    benchmark_multiply(avx::multiply);
    #endif

    #ifdef ENABLE_NEON
    benchmark_multiply(neon::multiply);
    #endif

    return 0;
}
