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

        // texture functions
        void (*m_GenTextures)(GLsizei,GLuint*);
        void (*m_DeleteTextures)(GLsizei,const GLuint*);
        void (*m_BindTexture)(GLenum,GLuint);
        void (*m_TexParameteri)(GLenum,GLenum,GLint);
        void (*m_TexImage2D)(GLenum,GLint,GLint,GLsizei,GLsizei,GLint,GLenum,GLenum,const void*);
        void (*m_TexImage3D)(GLenum,GLsizei,GLenum,GLsizei,GLsizei,GLsizei);
        void (*m_TexSubImage3D)(GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLenum,const void*);
        void (*m_TexStorage3D)(GLenum,GLsizei,GLenum,GLsizei,GLsizei,GLsizei);
    public:
        GL();

        inline void ClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) const noexcept { m_ClearColor(r, g, b, a); }
        inline void Clear(GLbitfield mask) const noexcept { m_Clear(mask); }

        inline GLuint CreateShader(GLenum shaderType) { return m_CreateShader(shaderType); }
        inline void DeleteShader(GLuint shader) { m_DeleteShader(shader); }
        inline void ShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length) { m_ShaderSource(shader, count, string, length); }
        inline void CompileShader(GLuint shader) { m_CompileShader(shader); }

        inline void GenTextures(GLsizei n, GLuint* textures) { m_GenTextures(n, textures); }
        inline void DeleteTextures(GLsizei n, const GLuint* textures) { m_DeleteTextures(n, textures); }
        inline void BindTexture(GLenum target, GLuint texture) { m_BindTexture(target, texture); }
        inline void TexParameteri(GLenum target, GLenum pname, GLint param) { m_TexParameteri(target, pname, param); }
        inline void TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * data) { m_TexImage2D(target, level, internalformat, width, height, border, format, type, data); }
        inline void TexImage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth) { m_TexImage3D(target, levels, internalformat, width, height, depth); }
        inline void TexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels) { m_TexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels); }
        inline void TexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth) { m_TexStorage3D(target, levels, internalformat, width, height, depth); }
    };
}

#endif