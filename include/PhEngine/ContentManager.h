#ifndef PHENGINE_CONTENTMANAGER_H_
#define PHENGINE_CONTENTMANAGER_H_

#include <cstdint>
#include <string>
#include <unordered_map>
#include <fstream>
#include <memory>
#include <cstdio>
#include <cstring>
#include <vector>
#include <optional>

#include "PhEngine/Internal/Setup.h"
#include "PhEngine/Exception.h"
#include "PhEngine/TextureAtlas.h"
#include "PhEngine/Graphics/Texture2D.h"
#include "PhEngine/Graphics/SpriteFont.h"
#include "PhEngine/Graphics/GL.h"

namespace PHENGINE_NAMESPACE
{
    class PHENGINE_EXPORT ContentManager
    {
    private:
        static const char m_FileHeader[8];

        static std::uint32_t ReadUInt32(char*);
        static std::uint16_t ReadUInt16(char*);

        std::uint16_t m_AtlasPageSize;
        std::uint16_t m_AtlasPageCount;

        std::unordered_map<std::string, Graphics::Texture2D> m_Textures;
        std::unordered_map<std::string, Graphics::SpriteFont> m_Fonts;

        Graphics::GL* m_GL;
        TextureAtlas* m_Atlas;
    public:
        inline ContentManager(const Graphics::GL* const gl)
        : m_GL(const_cast<Graphics::GL*>(gl)), m_Atlas(nullptr) { }

        inline TextureAtlas* GetTextureAtlas() { return m_Atlas; }

        inline ~ContentManager() { delete m_Atlas; }

        std::optional<Graphics::Texture2D*> GetTexture(const std::string&);
        void LoadContentFile(const std::string&);
    };
}

#endif