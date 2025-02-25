#ifndef PHENGINE_GRAPHICS_BATCHRENDERER_H_
#define PHENGINE_GRAPHICS_BATCHRENDERER_H_

#include "PhEngine/Internal/Setup.h"
#include "PhEngine/Window.h"
#include "PhEngine/Graphics/Shader.h"
#include "PhEngine/TextureAtlas.h"

namespace PHENGINE_GRAPHICS_NAMESPACE
{
    class PHENGINE_EXPORT BatchRenderer
    {
    private:
        Window* m_Window;
        GL* m_GL;
        std::shared_ptr<Shader> m_Shader;
        GLuint m_VAO, m_VBO, m_EBO;
    public:
        BatchRenderer(Window*);
        ~BatchRenderer();

        void Test(TextureAtlas*);
    };
}

#endif