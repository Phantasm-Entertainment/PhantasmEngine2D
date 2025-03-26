#ifndef PHENGINE_MATH_VECTOR_H_
#define PHENGINE_MATH_VECTOR_H_

#include <cstdint>
#include <cstring>
#include <type_traits>

#include "PhEngine/Internal/Setup.h"
#include "PhEngine/Math/MathInternal.h"

namespace PHENGINE_MATH_NAMESPACE
{
    template<Number t_Type>
    class Vector2
    {
    public:
        t_Type X;
        t_Type Y;

        Vector2() noexcept : X(static_cast<t_Type>(0)), Y(static_cast<t_Type>(0)) { }
        Vector2(t_Type x, t_Type y) noexcept : X(x), Y(y) { }

        Vector2 operator+(const Vector2& rhs) const
        {
            return Vector2(X + rhs.X, Y + rhs.Y);
        }

        Vector2& operator+=(const Vector2& rhs)
        {
            return *this + rhs;
        }
    };

    template<Number t_Type>
    class Vector3
    {
    public:
        t_Type X;
        t_Type Y;
        t_Type Z;

        Vector3() noexcept : X(static_cast<t_Type>(0)), Y(static_cast<t_Type>(0)), Z(static_cast<t_Type>(0)) { }
    };

    template<Number t_Type>
    class Vector4
    {
    public:
        t_Type X;
        t_Type Y;
        t_Type Z;
        t_Type W;

        Vector4() noexcept : X(static_cast<t_Type>(0)), Y(static_cast<t_Type>(0)), Z(static_cast<t_Type>(0)), W(static_cast<t_Type>(0)) { }
    };

    using Vector2f = Vector2<float>;
    using Vector3f = Vector3<float>;
    using Vector4f = Vector4<float>;
}

#endif