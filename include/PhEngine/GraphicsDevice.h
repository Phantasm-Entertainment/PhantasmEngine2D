#ifndef PHENGINE_GRAPHICSDEVICE_H_
#define PHENGINE_GRAPHICSDEVICE_H_

#ifdef PHENGINE_DEBUG
#include <iostream>
#endif
#include <string>

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
        std::string m_RendererName;

        void InitGL();
    public:
        GraphicsDevice();
        ~GraphicsDevice();

        inline const std::vector<Monitor>& GetMonitors() const noexcept { return m_Monitors; }
        inline const Monitor& GetPrimaryMonitor() const noexcept { return m_Monitors[0]; }

        inline GladGLContext* const GetGL() const noexcept { return m_GLCtx; }
        inline const std::string& GetRendererName() const noexcept { return m_RendererName; }
    };
}

#endif