#ifndef PHENGINE_TEXTUREATLAS_H_
#define PHENGINE_TEXTUREATLAS_H_

#include <cstdint>
#include <memory>
#include <vector>

#include "PhEngine/Internal/Setup.h"

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
        std::vector<AtlasPage> m_Pages;
    public:
        inline TextureAtlas(std::vector<AtlasPage> p)
        : m_Pages(std::move(p)) { }

        inline TextureAtlas(TextureAtlas&& atlas) : m_Pages(std::move(atlas.m_Pages)) { }
    };
}

#endif