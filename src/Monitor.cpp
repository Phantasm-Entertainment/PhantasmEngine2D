#include "PhEngine/Monitor.h"

namespace PHENGINE_NAMESPACE
{
    Resolution Monitor::GetCurrentResolution() const noexcept
    {
        const SDL_DisplayMode* dm = SDL_GetCurrentDisplayMode(m_ID);
        return Resolution(dm->w, dm->h);
    }
}