#ifndef PHENGINE_GRAPHICS_TEXTURE2D_H_
#define PHENGINE_GRAPHICS_TEXTURE2D_H_

#include <cstdint>

#include "PhEngine/Internal/Setup.h"
#include "PhEngine/Graphics/AtlasRef.h"

namespace PHENGINE_GRAPHICS_NAMESPACE
{
    class PHENGINE_EXPORT Texture2D
    {
    private:
        std::uint16_t m_Width, m_Height;
        AtlasRef m_AtlasRef;
    public:
        inline Texture2D(std::uint16_t w, std::uint16_t h, AtlasRef& ar) noexcept
        : m_Width(w), m_Height(h), m_AtlasRef(ar) { }

        inline std::uint16_t GetWidth() const noexcept { return m_Height; }
        inline std::uint16_t GetHeight() const noexcept { return m_Height; }
        inline const AtlasRef& GetAtlasRef() const noexcept { return m_AtlasRef; }
    };
}

#endif