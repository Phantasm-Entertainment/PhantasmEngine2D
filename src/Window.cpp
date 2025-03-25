#include "PhEngine/Window.h"

#include <iostream>

namespace PHENGINE_NAMESPACE
{
    Window::Window(GraphicsDevice* gd, std::shared_ptr<GameUpdate> gm) : m_GraphicsDevice(gd), m_GameUpdate(gm), m_Closed(false), m_Resolution(800, 600),
    m_Fullscreen(false)
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    #ifdef PHENGINE_DEBUG
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    #elif
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    #endif
        
        m_WinHandle = SDL_CreateWindow("Game", 800, 600, SDL_WINDOW_OPENGL);
       
        if (m_WinHandle == nullptr)
        {
            throw Exception("couldn't create window");
        }

        m_Context = SDL_GL_CreateContext(m_WinHandle);

        if (m_Context == nullptr)
        {
            throw Exception("couldn't create OpenGL context");
        }

        Center();
    }

    Window::~Window()
    {
        SDL_DestroyWindow(m_WinHandle);
    }

    void Window::Center() const noexcept
    {
        if (!m_Fullscreen)
        {
            const Resolution& res = m_GraphicsDevice->GetPrimaryMonitor().GetCurrentResolution();
            SDL_SetWindowPosition(m_WinHandle, (res.GetWidth() - m_Resolution.GetWidth()) / 2, (res.GetHeight() - m_Resolution.GetHeight()) / 2);
        }
    }

    void Window::SetSize(std::uint16_t w, std::uint16_t h) noexcept
    {
        if (!m_Fullscreen)
        {
            m_Resolution = Resolution(w, h);
            SDL_SetWindowSize(m_WinHandle, w, h);
            m_GraphicsDevice->GetGL()->Viewport(0, 0, m_Resolution.GetWidth(), m_Resolution.GetHeight());
        }
    }

    void Window::SetTitle(const std::string& title) noexcept
    {
        m_Title = title;
        SDL_SetWindowTitle(m_WinHandle, m_Title.c_str());
    }

    void Window::Clear(float r, float g, float b, float a) const noexcept
    {
        const Graphics::GL* gl = m_GraphicsDevice->GetGL();
        gl->ClearColor(r, g, b, a);
        gl->Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    bool Window::Update()
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_EVENT_KEY_DOWN:
                m_GameUpdate->m_Keys[event.key.key] = true;
                break;
            case SDL_EVENT_KEY_UP:
                m_GameUpdate->m_Keys[event.key.key] = false;
                break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                m_GameUpdate->m_MouseButtons[event.button.button] = true;
                break;
            case SDL_EVENT_MOUSE_BUTTON_UP:
                m_GameUpdate->m_MouseButtons[event.button.button] = false;
                break;
            case SDL_EVENT_MOUSE_MOTION:
                m_GameUpdate->m_MousePos.X = event.motion.x;
                m_GameUpdate->m_MousePos.Y = event.motion.y;
                break;
            case SDL_EVENT_QUIT:
                m_Closed = true;
                break;
            }
        }

        return m_Closed;
    }

    void Window::SwapBuffers()
    {
        SDL_GL_SwapWindow(m_WinHandle);
    }
}
