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
        "layout (location=2) in vec4 colour;\n"
        "uniform vec2 windowSize;\n"
        "out vec3 texCoords;\n"
        "out vec4 texColour;\n"
        "void main(){\n"
        "gl_Position=vec4(verts.x * (2.0 / windowSize.x) - 1.0, verts.y * (-2.0 / windowSize.y) + 1.0, 0.0, 1.0);\n"
        "texCoords=vec3(texs.xyz);texColour=vec4(colour.xyzw);}",

        "#version 330 core\n"
        "out vec4 fragColour;\n"
        "in vec3 texCoords;\n"
        "in vec4 texColour;\n"
        "uniform sampler2DArray atlas;\n"
        "void main(){\n"
        "fragColour=texelFetch(atlas, ivec3(texCoords.xyz), 0) * texColour;"
        "if(fragColour.w==0){discard;}}");

        m_GL->GenVertexArrays(1, &m_VAO);
        m_GL->GenBuffers(1, &m_VBO);
        m_GL->GenBuffers(1, &m_EBO);

        m_GL->BindVertexArray(m_VAO);
        m_GL->BindBuffer(GL_ARRAY_BUFFER, m_VBO);
        m_GL->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

        m_GL->BufferData(GL_ARRAY_BUFFER, 36 * sizeof(float) * PHENGINE_BATCHRENDERER_MAXJOBS, nullptr, GL_STREAM_DRAW);

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

        m_GL->VertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
        m_GL->EnableVertexAttribArray(0);
        m_GL->VertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(2 * sizeof(float)));
        m_GL->EnableVertexAttribArray(1);
        m_GL->VertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(5 * sizeof(float)));
        m_GL->EnableVertexAttribArray(2);
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

        m_GL->Enable(GL_BLEND);
        m_GL->BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        m_Shader->Use();
        m_Shader->SetUniform("windowSize", Math::Vector2f(m_Window->GetSize().GetWidth(), m_Window->GetSize().GetHeight()));
        m_ContentManager->GetTextureAtlas()->Use();
        m_GL->BindVertexArray(m_VAO);
        float vData[36];

        for (int i = 0; i < m_Jobs.size(); ++i)
        {
            float* colourF = m_Jobs[i].m_Colour.GetFloatData();

            vData[0] = m_Jobs[i].m_Rect.X;
            vData[1] = m_Jobs[i].m_Rect.Y;
            vData[2] = m_Jobs[i].m_Src.X + static_cast<float>(m_Jobs[i].m_AtlasRef.GetX());
            vData[3] = m_Jobs[i].m_Src.Y + static_cast<float>(m_Jobs[i].m_AtlasRef.GetY());
            vData[4] = static_cast<float>(m_Jobs[i].m_AtlasRef.GetPage());
            vData[5] = colourF[0];
            vData[6] = colourF[1];
            vData[7] = colourF[2];
            vData[8] = colourF[3];

            vData[9] = m_Jobs[i].m_Rect.X + m_Jobs[i].m_Rect.Width;
            vData[10] = m_Jobs[i].m_Rect.Y;
            vData[11] = m_Jobs[i].m_Src.X + m_Jobs[i].m_Src.Width + static_cast<float>(m_Jobs[i].m_AtlasRef.GetX());
            vData[12] = m_Jobs[i].m_Src.Y + static_cast<float>(m_Jobs[i].m_AtlasRef.GetY());
            vData[13] = static_cast<float>(m_Jobs[i].m_AtlasRef.GetPage());
            vData[14] = colourF[0];
            vData[15] = colourF[1];
            vData[16] = colourF[2];
            vData[17] = colourF[3];

            vData[18] = m_Jobs[i].m_Rect.X + m_Jobs[i].m_Rect.Width;
            vData[19] = m_Jobs[i].m_Rect.Y + m_Jobs[i].m_Rect.Height;
            vData[20] = m_Jobs[i].m_Src.X + m_Jobs[i].m_Src.Width + static_cast<float>(m_Jobs[i].m_AtlasRef.GetX());
            vData[21] = m_Jobs[i].m_Src.Y + m_Jobs[i].m_Src.Height + static_cast<float>(m_Jobs[i].m_AtlasRef.GetY());
            vData[22] = static_cast<float>(m_Jobs[i].m_AtlasRef.GetPage());
            vData[23] = colourF[0];
            vData[24] = colourF[1];
            vData[25] = colourF[2];
            vData[26] = colourF[3];

            vData[27] = m_Jobs[i].m_Rect.X;
            vData[28] = m_Jobs[i].m_Rect.Y + m_Jobs[i].m_Rect.Height;
            vData[29] = m_Jobs[i].m_Src.X + static_cast<float>(m_Jobs[i].m_AtlasRef.GetX());
            vData[30] = m_Jobs[i].m_Src.Y + m_Jobs[i].m_Src.Height + static_cast<float>(m_Jobs[i].m_AtlasRef.GetY());
            vData[31] = static_cast<float>(m_Jobs[i].m_AtlasRef.GetPage());
            vData[32] = colourF[0];
            vData[33] = colourF[1];
            vData[34] = colourF[2];
            vData[35] = colourF[3];

            m_GL->BufferSubData(GL_ARRAY_BUFFER, i * sizeof(vData), sizeof(vData), vData);
        }

        m_GL->DrawElements(GL_TRIANGLES, 6 * m_Jobs.size(), GL_UNSIGNED_INT, 0);
        m_Jobs.clear();
    }

    void BatchRenderer::Draw(Texture2D* texture, const Math::Vector2f& pos)
    {
        if (!m_Began)
        {
            throw Exception("haven't called begin");
        }

        m_Jobs.emplace_back(Math::Rectanglef(pos.X, pos.Y, texture->GetWidth(), texture->GetHeight()), Math::Rectanglef(0, 0, texture->GetWidth(), texture->GetHeight()), texture->GetAtlasRef());
    }

    void BatchRenderer::Draw(Texture2D* texture, const Math::Vector2f& pos, const Colour& colour)
    {
        if (!m_Began)
        {
            throw Exception("haven't called begin");
        }

        m_Jobs.emplace_back(Math::Rectanglef(pos.X, pos.Y, texture->GetWidth(), texture->GetHeight()), Math::Rectanglef(0, 0, texture->GetWidth(), texture->GetHeight()), texture->GetAtlasRef(), colour);
    }

    void BatchRenderer::DrawString(SpriteFont* font, const std::string& text, const Math::Vector2f& pos)
    {
        if (!m_Began)
        {
            throw Exception("haven't called begin");
        }

        Math::Vector2f textPos(pos.X, pos.Y + static_cast<float>(font->GetLineSpacing()));

        for (char c : text)
        {
            SpriteFontChar* fontChar = font->GetChar(c);

            if (fontChar == nullptr)
            {
                continue;
            }

            if (c == 32)
            {
                textPos.X += fontChar->GetAdvance();
            }
            else if (c == 10)
            {
                textPos.Y += static_cast<float>(font->GetLineSpacing());
                textPos.X = pos.X;
            }
            else
            {
                m_Jobs.emplace_back(
                Math::Rectanglef(textPos.X + static_cast<float>(fontChar->GetBearingX()), textPos.Y - static_cast<float>(fontChar->GetBearingY()), static_cast<float>(fontChar->GetWidth()), static_cast<float>(fontChar->GetHeight())),
                Math::Rectanglef(0.0f, 0.0f, static_cast<float>(fontChar->GetWidth()), static_cast<float>(fontChar->GetHeight())),
                fontChar->GetAtlasRef());
                textPos.X += static_cast<float>(fontChar->GetAdvance());
            }
        }
    }
}