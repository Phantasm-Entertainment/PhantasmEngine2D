#include "PhEngine/GraphicsDevice.h"

namespace PHENGINE_NAMESPACE
{
    GraphicsDevice::GraphicsDevice() : m_GLCtx(nullptr)
    {
        int count;
        SDL_DisplayID* displayIds = SDL_GetDisplays(&count);

        if (count < 1)
        {
            throw Exception("???");
        }

        bool alreadyIn;

        for (int i = 0; i < count; ++i)
        {
            int modeCount;
            SDL_DisplayMode** displayModes = SDL_GetFullscreenDisplayModes(displayIds[i], &modeCount);

            if (displayModes == NULL)
            {
                SDL_free(displayIds);
                throw Exception("???");
            }

            std::vector<Resolution> res;
            float refreshRate = 0.0f;

            for (int j = 0; j < modeCount; ++j)
            {
                if (displayModes[j]->w < 800 || displayModes[j]->h < 600)
                {
                    continue;
                }

                alreadyIn = false;

                for (const Resolution& r : res)
                {
                    if (r.GetWidth() == displayModes[j]->w && r.GetHeight() == displayModes[j]->h)
                    {
                        alreadyIn = true;
                    }
                }

                if (!alreadyIn)
                {
                    res.emplace_back(displayModes[j]->w, displayModes[j]->h);
                }

                if (displayModes[j]->refresh_rate > refreshRate)
                {
                    refreshRate = displayModes[j]->refresh_rate;
                }
            }

            m_Monitors.emplace_back(displayIds[i], SDL_GetDisplayName(displayIds[i]), i == 0, std::move(res), refreshRate);
            SDL_free(displayModes);
        }
    }

    GraphicsDevice::~GraphicsDevice()
    {
        if (m_GLCtx != nullptr)
        {
            delete m_GLCtx;
        }
    }

#ifdef PHENGINE_DEBUG
    void APIENTRY opengl_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* user)
    {
        std::cerr << message << '\n';
    }
#endif

    void GraphicsDevice::InitGL()
    {
        m_GLCtx = new GladGLContext;

        if (gladLoadGLContext(m_GLCtx, SDL_GL_GetProcAddress) == 0)
        {
            delete m_GLCtx;
            m_GLCtx = nullptr;
            throw Exception("couldn't load OpenGL functions");
        }

    #ifdef PHENGINE_DEBUG
        std::cout << "Vendor: " << m_GLCtx->GetString(GL_VENDOR) << '\n';
        std::cout << "Renderer: " << m_GLCtx->GetString(GL_RENDERER) << '\n';
        std::cout << "Version: " << m_GLCtx->GetString(GL_VERSION) << '\n';
        m_GLCtx->Enable(GL_DEBUG_OUTPUT);
        m_GLCtx->Enable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        m_GLCtx->DebugMessageCallback(opengl_debug_callback, nullptr);
        m_GLCtx->DebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
        std::cout << "Enabled OpenGL debug messaging.\n";
    #endif
    }
}
