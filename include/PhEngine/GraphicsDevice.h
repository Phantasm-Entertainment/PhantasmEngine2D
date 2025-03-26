#ifndef PHENGINE_GRAPHICSDEVICE_H_
#define PHENGINE_GRAPHICSDEVICE_H_

#include <iostream>

#include "PhEngine/Internal/Setup.h"
#include "PhEngine/Exception.h"
#include "PhEngine/Monitor.h"
#include "PhEngine/Graphics/GL.h"

namespace PHENGINE_NAMESPACE
{
    class PHENGINE_EXPORT GraphicsDevice
    {
        friend class Game;
    private:
        std::vector<Monitor> m_Monitors;
        GladGLContext* m_GLCtx;

        void InitGL();
    public:
        GraphicsDevice();
        ~GraphicsDevice();

        inline const std::vector<Monitor>& GetMonitors() const noexcept { return m_Monitors; }
        inline const Monitor& GetPrimaryMonitor() const noexcept { return m_Monitors[0]; }

        inline GladGLContext* const GetGL() const noexcept { return m_GLCtx; }
    };
}

#endif