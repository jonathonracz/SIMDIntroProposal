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

static inline void benchmark_multiply(void (*impl)(float*, size_t, float))
{
    float multiplier = 0.5f;
    std::vector<float> buffer;

    for (size_t i = 256; i <= 8192; i *= 2)
    {
        buffer.clear();
        buffer.resize(i, 0.5f);

        auto start = std::chrono::steady_clock::now();
        (*impl)(buffer.data(), buffer.size(), multiplier);
        auto end = std::chrono::steady_clock::now();

        std::cout << std::chrono::duration<float, std::micro>(start - end).count() << " ms ";
    }

    std::cout << "\n";
}

int main(int argc, char** argv)
{
    benchmark_multiply(none::multiply);

    #ifdef ENABLE_SSE
    benchmark_multiply(sse::multiply);
    #endif

    #ifdef ENABLE_AVX
    benchmark_multiply(avx::multiply);
    #endif

    #ifdef ENABLE_NEON
    benchmark_multiply(neon::multiply);
    #endif

    return 0;
}
