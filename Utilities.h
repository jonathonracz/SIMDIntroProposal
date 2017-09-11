#pragma once

#include <vector>
#include <type_traits>
#include <random>

template<class T>
std::vector<T> genRandomData(size_t size)
{
    static_assert(std::is_arithmetic<T>::value,
        "Random type must be an arithmetic type!");

    std::vector<T> ret(size); // We don't care about alignment right now.

    for (size_t i = 0; i < size; ++i)
    {
        ret[i] = static_cast<T>()
    }

    return ret;
}
