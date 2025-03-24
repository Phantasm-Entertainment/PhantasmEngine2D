#ifndef PHENGINE_GRAPHICS_SHADER_H_
#define PHENGINE_GRAPHICS_SHADER_H_

#include <memory>
#include <string>
#include <iostream>

#include "PhEngine/Internal/Setup.h"
#include "PhEngine/GraphicsDevice.h"
#include "PhEngine/Window.h"
#include "PhEngine/Exception.h"
#include "PhEngine/Math/Vector.h"

namespace PHENGINE_GRAPHICS_NAMESPACE
{
    class PHENGINE_EXPORT Shader
    {
    private:
        Window* m_Window;
        GL* m_GL;
        GLuint m_Program;
    public:
        inline Shader(Window* win, GLuint p) : m_Window(win), m_GL(win->GetGraphicsDevice()->GetGL()), m_Program(p) { }

        void Use() const;
        void SetUniform(const std::string&, const Math::Vector2f&) const;

        static std::shared_ptr<Shader> CreateShader(Window*, const std::string&, const std::string&);
    };
}

#endif