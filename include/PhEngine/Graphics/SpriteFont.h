#ifndef PHENGINE_GRAPHICS_SPRITEFONT_H_
#define PHENGINE_GRAPHICS_SPRITEFONT_H_

#include <cstdint>
#include <string>

#include "PhEngine/Internal/Setup.h"
#include "PhEngine/Graphics/AtlasRef.h"

namespace PHENGINE_GRAPHICS_NAMESPACE
{
    class PHENGINE_EXPORT SpriteFontChar
    {
    private:
        std::uint8_t m_Code;
        std::uint16_t m_Width, m_Height;
        std::int32_t m_BearingX, m_BearingY, m_Advance;
        AtlasRef m_AtlasRef;
    public:
        inline SpriteFontChar(std::uint8_t c, std::uint16_t w, std::uint16_t h, std::int32_t bx, std::int32_t by, std::int32_t a, AtlasRef& r) noexcept
        : m_Code(c), m_Width(w), m_Height(h), m_BearingX(bx), m_BearingY(by), m_Advance(a), m_AtlasRef(r) { }

        inline std::uint8_t GetCode() const noexcept { return m_Code; }
        inline std::uint16_t GetWidth() const noexcept { return m_Width; }
        inline std::uint16_t GetHeight() const noexcept { return m_Height; }
        inline std::int32_t GetBearingX() const noexcept { return m_BearingX; }
        inline std::int32_t GetBearingY() const noexcept { return m_BearingY; }
        inline std::int32_t GetAdvance() const noexcept { return m_Advance; }
        inline const AtlasRef& GetAtlasRef() const noexcept { return m_AtlasRef; }
    };

    class PHENGINE_EXPORT SpriteFont
    {
    private:
        std::string m_Name;
        std::uint16_t m_Size;
        std::uint16_t m_Ascender, m_Descender, m_LineSpacing;
        SpriteFontChar** m_Chars;
    public:
        inline SpriteFont(const std::string& name, std::uint16_t s, std::uint16_t a, std::uint16_t d, std::uint16_t l, SpriteFontChar** c) noexcept
        : m_Name(name), m_Size(s), m_Ascender(a), m_Descender(d), m_LineSpacing(l), m_Chars(c) { }

        ~SpriteFont();
    };
}

#endif