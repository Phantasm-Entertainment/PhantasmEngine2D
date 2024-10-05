#ifndef PHENGINE_GRAPHICS_ATLASREF_H_
#define PHENGINE_GRAPHICS_ATLASREF_H_

#include <cstdint>

#include "PhEngine/Internal/Setup.h"

namespace PHENGINE_GRAPHICS_NAMESPACE
{
    class PHENGINE_EXPORT AtlasRef
    {
    private:
        std::uint8_t m_Page;
        std::uint16_t m_X, m_Y;
    public:
        inline AtlasRef(std::uint8_t p, std::uint16_t x, std::uint16_t y) noexcept
        : m_Page(p), m_X(x), m_Y(y) { }

        inline std::uint8_t GetPage() const noexcept { return m_Page; }
        inline std::uint16_t GetX() const noexcept { return m_X; }
        inline std::uint16_t GetY() const noexcept { return m_Y; }
    };
}

#endif