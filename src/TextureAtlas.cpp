#include "PhEngine/TextureAtlas.h"

namespace PHENGINE_NAMESPACE
{
    TextureAtlas::TextureAtlas(Graphics::GL* gl, std::vector<AtlasPage> pages)
    : m_GL(gl), m_Pages(std::move(pages))
    {
        m_GL->GenTextures(1, &m_TexArray);
        m_GL->BindTexture(GL_TEXTURE_2D_ARRAY, m_TexArray);
        m_GL->TexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        m_GL->TexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        m_GL->TexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        m_GL->TexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        m_GL->TexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, 4096, 4096, m_Pages.size());

        for (int i = 0; i < m_Pages.size(); ++i)
        {
            m_GL->TexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, 4096, 4096, 1, GL_RGBA, GL_UNSIGNED_BYTE, m_Pages[i].GetData());
        }
    }
}