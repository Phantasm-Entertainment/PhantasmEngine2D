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
        void (*m_Viewport)(GLint,GLint,GLsizei,GLsizei);

        // shader functions
        GLuint (*m_CreateShader)(GLenum);
        void (*m_DeleteShader)(GLuint);
        void (*m_ShaderSource)(GLuint,GLsizei,const GLchar**,const GLint*);
        void (*m_CompileShader)(GLuint);
        void (*m_GetShaderiv)(GLuint,GLenum,GLint*);
        void (*m_GetProgramiv)(GLuint,GLenum,GLint*);
        void (*m_GetShaderInfoLog)(GLuint,GLsizei,GLsizei*,GLchar*);
        void (*m_GetProgramInfoLog)(GLuint,GLsizei,GLsizei*,GLchar*);
        GLuint (*m_CreateProgram)();
        void (*m_AttachShader)(GLuint,GLuint);
        void (*m_LinkProgram)(GLuint);
        void (*m_DeleteProgram)(GLuint);
        void (*m_UseProgram)(GLuint);

        // texture functions
        void (*m_GenTextures)(GLsizei,GLuint*);
        void (*m_DeleteTextures)(GLsizei,const GLuint*);
        void (*m_BindTexture)(GLenum,GLuint);
        void (*m_TexParameteri)(GLenum,GLenum,GLint);
        void (*m_TexImage2D)(GLenum,GLint,GLint,GLsizei,GLsizei,GLint,GLenum,GLenum,const void*);
        void (*m_TexImage3D)(GLenum,GLsizei,GLenum,GLsizei,GLsizei,GLsizei);
        void (*m_TexSubImage3D)(GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLenum,const void*);
        void (*m_TexStorage3D)(GLenum,GLsizei,GLenum,GLsizei,GLsizei,GLsizei);

        // buffer functions
        void (*m_GenVertexArrays)(GLsizei,GLuint*);
        void (*m_GenBuffers)(GLsizei,GLuint*);
        void (*m_BindVertexArray)(GLuint);
        void (*m_BindBuffer)(GLenum,GLuint);
        void (*m_BufferData)(GLenum,GLsizeiptr,const void*,GLenum);
        void (*m_BufferSubData)(GLenum,GLintptr,GLsizeiptr,const void*);
        void (*m_VertexAttribPointer)(GLuint,GLint,GLenum,GLboolean,GLsizei,const void*);
        void (*m_EnableVertexAttribArray)(GLuint);
        void (*m_DeleteVertexArrays)(GLsizei,const GLuint*);
        void (*m_DeleteBuffers)(GLsizei,const GLuint*);

        // drawing functions
        void (*m_DrawElements)(GLenum,GLsizei,GLenum,const void*);
    public:
        GL();

        inline void ClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) const noexcept { m_ClearColor(r, g, b, a); }
        inline void Clear(GLbitfield mask) const noexcept { m_Clear(mask); }
        inline void Viewport(GLint x, GLint y, GLsizei width, GLsizei height) { m_Viewport(x, y, width, height); }

        inline GLuint CreateShader(GLenum shaderType) { return m_CreateShader(shaderType); }
        inline void DeleteShader(GLuint shader) { m_DeleteShader(shader); }
        inline void ShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length) { m_ShaderSource(shader, count, string, length); }
        inline void CompileShader(GLuint shader) { m_CompileShader(shader); }
        inline void GetShaderiv(GLuint shader, GLenum pname, GLint* params) { m_GetShaderiv(shader, pname, params); }
        inline void GetProgramiv(GLuint program, GLenum pname, GLint *params) { m_GetProgramiv(program, pname, params); }
        inline void GetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei *length, GLchar* infoLog) { m_GetShaderInfoLog(shader, maxLength, length, infoLog); }
        inline void GetProgramInfoLog(GLuint program, GLsizei maxLength, GLsizei *length, GLchar *infoLog) { m_GetProgramInfoLog(program, maxLength, length, infoLog); }
        inline GLuint CreateProgram() { return m_CreateProgram(); }
        inline void AttachShader(GLuint program, GLuint shader) { m_AttachShader(program, shader); }
        inline void LinkProgram(GLuint program) { m_LinkProgram(program); }
        inline void DeleteProgram(GLuint program) { m_DeleteProgram(program); }
        inline void UseProgram(GLuint program) { m_UseProgram(program); }

        inline void GenTextures(GLsizei n, GLuint* textures) { m_GenTextures(n, textures); }
        inline void DeleteTextures(GLsizei n, const GLuint* textures) { m_DeleteTextures(n, textures); }
        inline void BindTexture(GLenum target, GLuint texture) { m_BindTexture(target, texture); }
        inline void TexParameteri(GLenum target, GLenum pname, GLint param) { m_TexParameteri(target, pname, param); }
        inline void TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * data) { m_TexImage2D(target, level, internalformat, width, height, border, format, type, data); }
        inline void TexImage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth) { m_TexImage3D(target, levels, internalformat, width, height, depth); }
        inline void TexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels) { m_TexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels); }
        inline void TexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth) { m_TexStorage3D(target, levels, internalformat, width, height, depth); }

        inline void GenVertexArrays(GLsizei n, GLuint* arrays) { m_GenVertexArrays(n, arrays); }
        inline void GenBuffers(GLsizei n, GLuint* arrays) { m_GenBuffers(n, arrays); }
        inline void BindVertexArray(GLuint array) { m_BindVertexArray(array); }
        inline void BindBuffer(GLenum target, GLuint array) { m_BindBuffer(target, array); }
        inline void BufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage) { m_BufferData(target, size, data, usage); }
        inline void BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void* data) { m_BufferSubData(target, offset, size, data); }
        inline void VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) { m_VertexAttribPointer(index, size, type, normalized, stride, pointer); }
        inline void EnableVertexAttribArray(GLuint index) { m_EnableVertexAttribArray(index); }
        inline void DeleteVertexArrays(GLsizei n, const GLuint* arrays) { m_DeleteVertexArrays(n, arrays); }
        inline void DeleteBuffers(GLsizei n, const GLuint* arrays) { m_DeleteBuffers(n, arrays); }

        inline void DrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices) { m_DrawElements(mode, count, type, indices); }
    };
}

#endif