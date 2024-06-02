#ifndef PHENGINE_GRAPHICS_GL_H_
#define PHENGINE_GRAPHICS_GL_H_

#include <SDL3/SDL.h>

#include "PhEngine/Internal/Setup.h"
#include "PhEngine/Graphics/GLDefs.h"

namespace PHENGINE_GRAPHICS_NAMESPACE
{
    class PHENGINE_EXPORT GL
    {
    private:
        // basic stuff (clear)
        void (*m_ClearColor)(GLfloat,GLfloat,GLfloat,GLfloat);
        void (*m_Clear)(GLbitfield);

        // shader functions
        GLuint (*m_CreateShader)(GLenum);
        void (*m_DeleteShader)(GLuint);
        void (*m_ShaderSource)(GLuint,GLsizei,const GLchar**,const GLint*);
        void (*m_CompileShader)(GLuint);
    public:
        GL();

        inline void ClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) const noexcept { m_ClearColor(r, g, b, a); }
        inline void Clear(GLbitfield mask) const noexcept { m_Clear(mask); }

        inline GLuint CreateShader(GLenum shaderType) { return m_CreateShader(shaderType); }
        inline void DeleteShader(GLuint shader) { m_DeleteShader(shader); }
        inline void ShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length) { m_ShaderSource(shader, count, string, length); }
        inline void CompileShader(GLuint shader) { m_CompileShader(shader); }
    };
}

#endif