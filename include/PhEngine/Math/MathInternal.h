#ifndef PHENGINE_MATH_MATHINTERNAL_H_
#define PHENGINE_MATH_MATHINTERNAL_H_

#include <concepts>

#include "PhEngine/Internal/Setup.h"

namespace PHENGINE_MATH_NAMESPACE
{
    template<typename T>
    concept Number = std::integral<T> || std::floating_point<T>;
}

#endif