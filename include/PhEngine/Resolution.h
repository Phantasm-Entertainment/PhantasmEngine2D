#ifndef PHENGINE_RESOLUTION_H_
#define PHENGINE_RESOLUTION_H_

#include <cstdint>

#include "PhEngine/Internal/Setup.h"

namespace PHENGINE_NAMESPACE
{
    class PHENGINE_EXPORT Resolution
    {
    private:
        std::uint16_t m_Width, m_Height;
    public:
        inline Resolution(std::uint16_t w, std::uint16_t h) : m_Width(w), m_Height(h) { }

        inline std::uint16_t GetWidth() const noexcept { return m_Width; }
        inline std::uint16_t GetHeight() const noexcept { return m_Height; }
    };
}

#endif