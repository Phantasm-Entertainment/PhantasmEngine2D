#ifndef PHENGINE_GRAPHICS_SHADER_H_
#define PHENGINE_GRAPHICS_SHADER_H_

#include <memory>

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

        Shader();
    public:
        
    };
}

#endif