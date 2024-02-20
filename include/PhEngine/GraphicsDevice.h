#ifndef PHENGINE_GRAPHICSDEVICE_H_
#define PHENGINE_GRAPHICSDEVICE_H_

#include "PhEngine/Internal/Setup.h"
#include "PhEngine/Exception.h"
#include "PhEngine/Monitor.h"

namespace PHENGINE_NAMESPACE
{
    class PHENGINE_EXPORT GraphicsDevice
    {
        friend class Game;
    private:
        std::vector<Monitor> m_Monitors;
    public:
        GraphicsDevice();
        ~GraphicsDevice();

        inline const std::vector<Monitor>& GetMonitors() const noexcept { return m_Monitors; }
        inline const Monitor& GetPrimaryMonitor() const noexcept { return m_Monitors[0]; }
    };
}

#endif