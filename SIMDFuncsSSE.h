#pragma once

#include <xmmintrin.h>

namespace sse
{

// Optimizing for Intel Haswell - the generation of the mid-2015 MacBook
// lineup.
void multiply(float* data, size_t size, float multiplier)
{
    // Broadcast multiplier to all 4 32 bit spaces in the 128 bit register.
    __m128 packedMultiplier = _mm_set1_ps(multiplier);
    __m128 accum0;

    for (size_t i = 0; size - i >= 4; i += 4)
    {
        // Load all values into our accumulators.
        accum0 = _mm_loadu_ps(data + i);
        accum0 = _mm_mul_ps(packedMultiplier, accum0);
        _mm_store_ps(data + i, accum0);
    }
}

}
