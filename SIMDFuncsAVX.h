#pragma once

#include <immintrin.h>

namespace avx
{

void multiply(float* data, size_t size, float multiplier)
{
    // Broadcast multiplier to all 4 32 bit spaces in the 128 bit register.
    __m256 packedMultiplier = _mm256_set1_ps(multiplier);
    __m256 accum0;

    for (size_t i = 0; size - i >= 8; i += 8)
    {
        // Load all values into our accumulators.
        accum0 = _mm256_loadu_ps(data + i);
        accum0 = _mm256_mul_ps(packedMultiplier, accum0);
        _mm256_store_ps(data + i, accum0);
    }
}

}
