#ifndef PHENGINE_MATH_MATRIX_H_
#define PHENGINE_MATH_MATRIX_H_

#include <cstdint>
#include <cstring>
#include <type_traits>
#include <iostream>

#include "PhEngine/Internal/Setup.h"
#include "PhEngine/Exception.h"

namespace PHENGINE_MATH_NAMESPACE
{
    typedef Matrix<float, 4, 4> Matrix4f;

    // matrix of flexible type and column/row size, in row major order (needs to be transposed when using glUniform)
    template<typename t_Type, std::size_t t_Columns, std::size_t t_Rows>
    class Matrix
    {
        static_assert(t_Columns > 0 && t_Columns < 5, "invalid column size");
        static_assert(t_Rows > 0 && t_Rows < 5, "invalid row size");
        static_assert(std::is_floating_point_v(t_Type) || std::is_integral_v(t_Type), "invalid type");
    private:
        std::size_t m_Columns, m_Rows;
        t_Type m_Data[t_Columns * t_Rows];
    public:
        Matrix() noexcept : m_Columns(t_Columns), m_Rows(t_Rows)
        {
            std::memset(m_Data, 0, sizeof(m_Data));
        }

        const t_Type* const GetData() const noexcept { return m_Data; }

        // TODO: FIX
        t_Type* operator[](std::int64_t i)
        {
            if (i < 0 || i > m_Columns * m_Rows)
            {
                throw Exception("out of bounds for Matrix::operator[]");
            }

            return &m_Data[i];
        }

        Matrix& Identity() noexcept
        {
            std::memset(m_Data, 0, sizeof(m_Data));

            if (m_Columns == m_Rows)
            {
                for (std::size_t i = 0; i < m_Columns * m_Rows; i += m_Rows)
                {
                    m_Data[i] = static_cast<t_Type>(1);
                }
            }
        }

        Matrix& OrthographicProjection(t_Type top, t_Type bottom, t_Type left, t_Type right, t_Type near, t_Type far) noexcept
        {
            if (m_Rows == 4 && m_Columns == 4)
            {
                Identity();
                m_Data[0] = static_cast<t_Type>(2) / (right - left);
                m_Data[3] = -((right + left) / (right - left));
                m_Data[5] = static_cast<t_Type>(2) / (top - bottom);
                m_Data[7] = -((top + bottom) / (top - bottom));
                m_Data[10] = static_cast<t_Type>(-2) / (far - near);
                m_Data[11] = -((far + near) / (far - near));
                //m_Data[15] = static_cast<t_Type>(1);
            }
        }
    };
}

template<typename t_Type, std::size_t t_Columns, std::size_t t_Rows>
std::ostream& operator<<(std::ostream& os, const PHENGINE_MATH_NAMESPACE::Matrix<t_Type, t_Columns, t_Rows>& m)
{
    os << "Matrix [";

    for (int i = 0; i < m.m_Rows * m.m_Columns; ++i)
    {
        if (i == m.m_Rows * m.m_Columns - 1)
        {
            os << std::to_string(m.m_Data[i]);
        }
        else
        {
            os << std::to_string(m.m_Data[i]) << ", ";
        }
    }

    os << "]";
    return os;
}

#endif