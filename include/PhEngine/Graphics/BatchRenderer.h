#ifndef PHENGINE_GRAPHICS_BATCHRENDERER_H_
#define PHENGINE_GRAPHICS_BATCHRENDERER_H_

#include <vector>

#include "PhEngine/Internal/Setup.h"
#include "PhEngine/Window.h"
#include "PhEngine/ContentManager.h"
#include "PhEngine/Graphics/Shader.h"
#include "PhEngine/TextureAtlas.h"
#include "PhEngine/Math/Rectangle.h"
#include "PhEngine/Graphics/Colour.h"

#define PHENGINE_BATCHRENDERER_MAXJOBS 102400

namespace PHENGINE_GRAPHICS_NAMESPACE
{
    // internal use only
    struct PHENGINE_EXPORT BatchJob
    {
    public:
        Math::Rectanglef m_Rect;
        Math::Rectanglef m_Src;
        AtlasRef m_AtlasRef;
        Colour m_Colour;

        inline BatchJob(const Math::Rectanglef& r, const Math::Rectanglef& s, const AtlasRef& f) : m_Rect(r), m_Src(s), m_AtlasRef(f) { }

        inline BatchJob(const Math::Rectanglef& r, const Math::Rectanglef& s, const AtlasRef& f, const Colour& c) : m_Rect(r), m_Src(s), m_AtlasRef(f), m_Colour(c) { }
    };
    
    class PHENGINE_EXPORT BatchRenderer
    {
    private:
        Window* m_Window;
        ContentManager* m_ContentManager;
        GladGLContext* m_GL;
        std::shared_ptr<Shader> m_Shader;
        GLuint m_VAO, m_VBO, m_EBO;
        std::unique_ptr<float[]> m_Verts;
        std::vector<BatchJob> m_Jobs;
        bool m_Began;
    public:
        BatchRenderer(Window*, ContentManager*);
        ~BatchRenderer();

        void Begin();
        void End();
        void Draw(Texture2D*, const Math::Vector2f&);
        void Draw(Texture2D*, const Math::Rectanglef&);
        void Draw(Texture2D*, const Math::Vector2f&, const Colour&);
        void Draw(Texture2D*, const Math::Rectanglef&, const Math::Rectanglef&);
        void DrawString(SpriteFont*, const std::string&, const Math::Vector2f&);
    };
}

#endif