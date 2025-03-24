#ifndef PHENGINE_MATH_RECTANGLE_H_
#define PHENGINE_MATH_RECTANGLE_H_

#include <cstdint>
#include <cstring>

#include "PhEngine/Internal/Setup.h"
#include "PhEngine/Math/MathInternal.h"

namespace PHENGINE_MATH_NAMESPACE
{
    template<Number t_Type>
    class Rectangle
    {
    public:
        t_Type X, Y, Width, Height;

        Rectangle() noexcept : X(static_cast<t_Type>(0)), Y(static_cast<t_Type>(0)),
        Width(static_cast<t_Type>(0)), Height(static_cast<t_Type>(0)) { }

        Rectangle(t_Type x, t_Type y, t_Type w, t_Type h) noexcept : X(x), Y(y), Width(w), Height(h) { }
    };

    using Rectanglef = Rectangle<float>;
}

#endif