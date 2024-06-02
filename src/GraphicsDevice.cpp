#include "PhEngine/GraphicsDevice.h"

namespace PHENGINE_NAMESPACE
{
    GraphicsDevice::GraphicsDevice() : m_GL(nullptr)
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
            const SDL_DisplayMode** displayModes = SDL_GetFullscreenDisplayModes(displayIds[i], &modeCount);

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

                float r = static_cast<float>(displayModes[j]->refresh_rate);

                if (r > refreshRate)
                {
                    refreshRate = r;
                }
            }

            m_Monitors.emplace_back(displayIds[i], SDL_GetDisplayName(displayIds[i]), i == 0, std::move(res), refreshRate);
            SDL_free(displayModes);
        }
    }

    GraphicsDevice::~GraphicsDevice()
    {
        if (m_GL)
        {
            delete m_GL;
        }
    }

    void GraphicsDevice::InitGL()
    {
        m_GL = new Graphics::GL();
    }
}