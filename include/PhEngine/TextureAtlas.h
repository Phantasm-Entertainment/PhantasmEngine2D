#ifndef PHENGINE_TEXTUREATLAS_H_
#define PHENGINE_TEXTUREATLAS_H_

#include <cstdint>
#include <memory>
#include <vector>

#include "PhEngine/Internal/Setup.h"
#include "PhEngine/Graphics/GL.h"

namespace PHENGINE_NAMESPACE
{
    class PHENGINE_EXPORT AtlasPage
    {
    private:
        std::size_t m_Width;
        std::size_t m_Height;
        std::unique_ptr<unsigned char[]> m_Data;
    public:
        inline AtlasPage(std::size_t w, std::size_t h, std::unique_ptr<unsigned char[]> d)
        : m_Width(w), m_Height(h), m_Data(std::move(d)) { }

        // thanks MSVC
        inline AtlasPage(AtlasPage&& page) : m_Width(page.m_Width), m_Height(page.m_Height), m_Data(std::move(page.m_Data)) { }

        inline unsigned char* GetData() { return m_Data.get(); }
    };

    class PHENGINE_EXPORT TextureAtlas
    {
    private:
        Graphics::GL* m_GL;
        std::vector<AtlasPage> m_Pages;
        GLuint m_TexArray;
    public:
        TextureAtlas(Graphics::GL*, std::vector<AtlasPage>);

        inline void Use() { m_GL->BindTexture(GL_TEXTURE_2D_ARRAY, m_TexArray); }

        inline ~TextureAtlas() { if (m_TexArray != 0) { m_GL->DeleteTextures(1, &m_TexArray); } }

        inline TextureAtlas(TextureAtlas&& atlas) : m_Pages(std::move(atlas.m_Pages)) { atlas.m_TexArray = 0; }
    };
}

#endif