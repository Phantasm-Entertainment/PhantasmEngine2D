#include "PhEngine/Graphics/BatchRenderer.h"

namespace PHENGINE_GRAPHICS_NAMESPACE
{
    BatchRenderer::BatchRenderer(Window* win, ContentManager* cm) : m_Window(win), m_ContentManager(cm), m_Began(false)
    {
        m_GL = m_Window->GetGraphicsDevice()->GetGL();
        m_Shader = Shader::CreateShader(m_Window,
        "#version 330 core\n"
        "layout (location=0) in vec2 verts;\n"
        "layout (location=1) in vec3 texs;\n"
        "uniform vec2 windowSize;\n"
        "out vec3 texData;\n"
        "void main(){\n"
        "gl_Position=vec4(verts.x * (2.0 / windowSize.x) - 1.0, verts.y * (-2.0 / windowSize.y) + 1.0, 0.0, 1.0);\n"
        "texData=vec3(texs.xyz);}",

        "#version 330 core\n"
        "out vec4 fragColour;\n"
        "in vec3 texData;\n"
        "uniform sampler2DArray atlas;\n"
        "void main(){\n"
        "fragColour=texelFetch(atlas, ivec3(texData.xyz), 0);}");

        m_GL->GenVertexArrays(1, &m_VAO);
        m_GL->GenBuffers(1, &m_VBO);
        m_GL->GenBuffers(1, &m_EBO);

        m_GL->BindVertexArray(m_VAO);
        m_GL->BindBuffer(GL_ARRAY_BUFFER, m_VBO);
        m_GL->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

        m_GL->BufferData(GL_ARRAY_BUFFER, 20 * sizeof(float) * PHENGINE_BATCHRENDERER_MAXJOBS, nullptr, GL_DYNAMIC_DRAW);

        GLuint* indices = new GLuint[6 * PHENGINE_BATCHRENDERER_MAXJOBS];
        GLuint ind = 0;

        for (std::size_t i = 0; i < 6 * PHENGINE_BATCHRENDERER_MAXJOBS; i += 6)
        {
            indices[i] = ind;
            indices[i+1] = ind + 1;
            indices[i+2] = ind + 2;
            indices[i+3] = ind + 2;
            indices[i+4] = ind + 3;
            indices[i+5] = ind;
            ind += 4;
        }

        m_GL->BufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * PHENGINE_BATCHRENDERER_MAXJOBS * sizeof(GLuint), indices, GL_STATIC_DRAW);
        delete[] indices;

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

    void BatchRenderer::Begin()
    {
        if (m_Began)
        {
            throw Exception("already began");
        }

        m_Began = true;
    }

    void BatchRenderer::End()
    {
        if (!m_Began)
        {
            throw Exception("haven't called begin");
        }

        m_Began = false;

        if (m_Jobs.empty()) { return; }

        m_Shader->Use();
        m_Shader->SetUniform("windowSize", Math::Vector2f(m_Window->GetSize().GetWidth(), m_Window->GetSize().GetHeight()));
        m_ContentManager->GetTextureAtlas()->Use();
        m_GL->BindVertexArray(m_VAO);
        m_GL->BindBuffer(GL_ARRAY_BUFFER, m_VBO);
        m_GL->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        float* vData = new float[20];

        for (int i = 0; i < m_Jobs.size(); ++i)
        {
            vData[0] = m_Jobs[i].m_Rect.X;
            vData[1] = m_Jobs[i].m_Rect.Y;
            vData[2] = m_Jobs[i].m_Src.X + static_cast<float>(m_Jobs[i].m_AtlasRef.GetX());
            vData[3] = m_Jobs[i].m_Src.Y + static_cast<float>(m_Jobs[i].m_AtlasRef.GetY());
            vData[4] = static_cast<float>(m_Jobs[i].m_AtlasRef.GetPage());

            vData[5] = m_Jobs[i].m_Rect.X + m_Jobs[i].m_Rect.Width;
            vData[6] = m_Jobs[i].m_Rect.Y;
            vData[7] = m_Jobs[i].m_Src.X + m_Jobs[i].m_Src.Width + static_cast<float>(m_Jobs[i].m_AtlasRef.GetX());
            vData[8] = m_Jobs[i].m_Src.Y + static_cast<float>(m_Jobs[i].m_AtlasRef.GetY());
            vData[9] = static_cast<float>(m_Jobs[i].m_AtlasRef.GetPage());

            vData[10] = m_Jobs[i].m_Rect.X + m_Jobs[i].m_Rect.Width;
            vData[11] = m_Jobs[i].m_Rect.Y + m_Jobs[i].m_Rect.Height;
            vData[12] = m_Jobs[i].m_Src.X + m_Jobs[i].m_Src.Width + static_cast<float>(m_Jobs[i].m_AtlasRef.GetX());
            vData[13] = m_Jobs[i].m_Src.Y + m_Jobs[i].m_Src.Height + static_cast<float>(m_Jobs[i].m_AtlasRef.GetY());
            vData[14] = static_cast<float>(m_Jobs[i].m_AtlasRef.GetPage());

            vData[15] = m_Jobs[i].m_Rect.X;
            vData[16] = m_Jobs[i].m_Rect.Y + m_Jobs[i].m_Rect.Height;
            vData[17] = m_Jobs[i].m_Src.X + static_cast<float>(m_Jobs[i].m_AtlasRef.GetX());
            vData[18] = m_Jobs[i].m_Src.Y + m_Jobs[i].m_Src.Height + static_cast<float>(m_Jobs[i].m_AtlasRef.GetY());
            vData[19] = static_cast<float>(m_Jobs[i].m_AtlasRef.GetPage());

            m_GL->BufferSubData(GL_ARRAY_BUFFER, i * 20 * sizeof(float), 20 * sizeof(float), vData);
        }

        delete[] vData;
        m_GL->DrawElements(GL_TRIANGLES, 6 * m_Jobs.size(), GL_UNSIGNED_INT, 0);
        m_Jobs.clear();
    }

    void BatchRenderer::Draw(Texture2D* texture, Math::Vector2f pos)
    {
        if (!m_Began)
        {
            throw Exception("haven't called begin");
        }

        m_Jobs.emplace_back(Math::Rectanglef(pos.X, pos.Y, texture->GetWidth(), texture->GetHeight()), Math::Rectanglef(0, 0, texture->GetWidth(), texture->GetHeight()), texture->GetAtlasRef());
    }
}