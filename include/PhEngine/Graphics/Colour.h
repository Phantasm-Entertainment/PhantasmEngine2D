#ifndef PHENGINE_GRAPHICS_COLOUR_H_
#define PHENGINE_GRAPHICS_COLOUR_H_

#include <cstdint>

#include "PhEngine/Internal/Setup.h"

namespace PHENGINE_GRAPHICS_NAMESPACE
{
    class Colour
    {
    private:
        float m_FloatData[4];
    public:
        std::uint8_t R, G, B, A;

        inline Colour() noexcept :
        R(0xFF), G(0xFF), B(0xFF), A(0xFF) { }

        inline Colour(std::uint8_t r, std::uint8_t g, std::uint8_t b) noexcept :
        R(r), G(g), B(b), A(0xFF) { }

        inline Colour(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) noexcept :
        R(r), G(g), B(b), A(a) { }

        inline Colour(const Colour& c) noexcept :
        R(c.R), G(c.G), B(c.B), A(c.A) { }

        inline float* GetFloatData() noexcept
        {
            m_FloatData[0] = (1.0f/255.0f) * static_cast<float>(R);
            m_FloatData[1] = (1.0f/255.0f) * static_cast<float>(G);
            m_FloatData[2] = (1.0f/255.0f) * static_cast<float>(B);
            m_FloatData[3] = (1.0f/255.0f) * static_cast<float>(A);
            return m_FloatData;
        }
    };
}

#endif