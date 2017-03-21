#pragma once

namespace none
{

void multiply(float* data, size_t size, float multiplier)
{
    for (size_t i = 0; i < size; ++i)
    {
        *data *= multiplier;
    }
}

}
