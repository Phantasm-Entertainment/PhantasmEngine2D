#include "PhEngine/Window.h"

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

namespace PHENGINE_NAMESPACE
{
    Window::Window(GraphicsDevice* gd) : m_GraphicsDevice(gd), m_Closed(false), m_Resolution(800, 600),
    m_Fullscreen(false)
    {
        
        // vulkan stuff

        // finalise

        Center();
        Clear();
    }

    Window::~Window()
    {
        
    }

    void Window::Center() const noexcept
    {
        if (!m_Fullscreen)
        {
            const Resolution& res = m_GraphicsDevice->GetPrimaryMonitor().GetMaxResolution();
            //SetWindowPos(m_ImplWindowData->m_WinHandle, NULL, (res.GetWidth() - m_Resolution.GetWidth()) / 2, (res.GetHeight() - m_Resolution.GetHeight()) / 2, 0, 0, SWP_NOSIZE);
        }
    }

    void Window::Clear(float r, float g, float b, float a) const noexcept
    {
        //glClearColor(r, g, b, a);
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    bool Window::Update()
    {
        
    }

    void Window::SwapBuffers()
    {
        
    }
}
