#ifndef PHENGINE_GRAPHICS_SHADER_H_
#define PHENGINE_GRAPHICS_SHADER_H_

#include <memory>
#include <iostream>

#include "PhEngine/Internal/Setup.h"
#include "PhEngine/GraphicsDevice.h"
#include "PhEngine/Window.h"

namespace PHENGINE_GRAPHICS_NAMESPACE
{
    class PHENGINE_EXPORT Shader
    {
    private:
        Window* m_Window;
        GLuint m_Program;
    public:
        inline Shader(Window* win, GLuint p) : m_Window(win), m_Program(p) { }

        void Use();

        static std::shared_ptr<Shader> CreateShader(Window*, const std::string&, const std::string&);
    };
}

#endif