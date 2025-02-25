#include "PhEngine/Graphics/BatchRenderer.h"

namespace PHENGINE_GRAPHICS_NAMESPACE
{
    BatchRenderer::BatchRenderer(Window* win) : m_Window(win)
    {
        m_GL = m_Window->GetGraphicsDevice()->GetGL();
        m_Shader = Shader::CreateShader(m_Window,
        "#version 330 core\n"
        "layout (location=0) in vec2 verts;\n"
        "layout (location=1) in vec3 texs;\n"
        "out vec3 texData;\n"
        "void main(){\n"
        "gl_Position=vec4(verts.xy, 0.0, 1.0);\n"
        "texData=vec3(texs.xyz);}",

        "#version 330 core\n"
        "out vec4 fragColour;\n"
        "in vec3 texData;\n"
        "uniform sampler2DArray atlas;\n"
        "void main(){\n"
        "fragColour=texelFetch(atlas, ivec3(texData.xyz), 0);}");
        //"fragColour=vec4(1.0, 0.0, 0.0, 1.0);}");

        m_GL->GenVertexArrays(1, &m_VAO);
        m_GL->GenBuffers(1, &m_VBO);
        m_GL->GenBuffers(1, &m_EBO);

        m_GL->BindVertexArray(m_VAO);
        m_GL->BindBuffer(GL_ARRAY_BUFFER, m_VBO);
        m_GL->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

        float testVerts[] =
        {
            -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
            0.5f, 0.5f, 1920.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 1920.0f, 1080.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 1080.0f, 0.0f
        };
        GLuint testIndices[] = { 0, 1, 2, 2, 3, 0 };

        m_GL->BufferData(GL_ARRAY_BUFFER, sizeof(testVerts), testVerts, GL_STATIC_DRAW);
        m_GL->BufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(testIndices), testIndices, GL_STATIC_DRAW);

        m_GL->VertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        m_GL->EnableVertexAttribArray(0);
        m_GL->VertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
        m_GL->EnableVertexAttribArray(1);
    }

    BatchRenderer::~BatchRenderer()
    {
        m_GL->DeleteVertexArrays(1, &m_VAO);
        m_GL->DeleteBuffers(1, &m_EBO);
        m_GL->DeleteBuffers(1, &m_VBO);
    }

    void BatchRenderer::Test(TextureAtlas* atlas)
    {
        m_Shader->Use();
        atlas->Use();
        m_GL->BindVertexArray(m_VAO);
        m_GL->DrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}