#include "PhEngine/Graphics/SpriteFont.h"

namespace PHENGINE_GRAPHICS_NAMESPACE
{
    SpriteFont::~SpriteFont()
    {
        for (std::uint8_t i = 0; i < 126; ++i)
        {
            if (m_Chars[i])
            {
                delete m_Chars[i];
            }
        }

        delete[] m_Chars;
    }
}