#include "PhEngine/Graphics/GL.h"

#define GET_PROC_ADDRESS SDL_GL_GetProcAddress

namespace PHENGINE_GRAPHICS_NAMESPACE
{
    GL::GL()
    {
        m_ClearColor = (void(*)(GLfloat,GLfloat,GLfloat,GLfloat))GET_PROC_ADDRESS("glClearColor");
        m_Clear = (void(*)(GLbitfield))GET_PROC_ADDRESS("glClear");
        m_Viewport = (void(*)(GLint,GLint,GLsizei,GLsizei))GET_PROC_ADDRESS("glViewport");

        m_CreateShader = (GLuint(*)(GLenum))GET_PROC_ADDRESS("glCreateShader");
        m_DeleteShader = (void(*)(GLuint))GET_PROC_ADDRESS("glDeleteShader");
        m_ShaderSource = (void(*)(GLuint,GLsizei,const GLchar**,const GLint*))GET_PROC_ADDRESS("glShaderSource");
        m_CompileShader = (void(*)(GLuint))GET_PROC_ADDRESS("glCompileShader");
        m_GetShaderiv = (void(*)(GLuint,GLenum,GLint*))GET_PROC_ADDRESS("glGetShaderiv");
        m_GetProgramiv = (void(*)(GLuint,GLenum,GLint*))GET_PROC_ADDRESS("glGetProgramiv");
        m_GetShaderInfoLog = (void(*)(GLuint,GLsizei,GLsizei*,GLchar*))GET_PROC_ADDRESS("glGetShaderInfoLog");
        m_GetProgramInfoLog = (void(*)(GLuint,GLsizei,GLsizei*,GLchar*))GET_PROC_ADDRESS("glGetProgramInfoLog");
        m_CreateProgram = (GLuint(*)())GET_PROC_ADDRESS("glCreateProgram");
        m_AttachShader = (void(*)(GLuint,GLuint))GET_PROC_ADDRESS("glAttachShader");
        m_LinkProgram = (void(*)(GLuint))GET_PROC_ADDRESS("glLinkProgram");
        m_DeleteProgram = (void(*)(GLuint))GET_PROC_ADDRESS("glDeleteProgram");
        m_UseProgram = (void(*)(GLuint))GET_PROC_ADDRESS("glUseProgram");

        m_GenTextures = (void(*)(GLsizei,GLuint*))GET_PROC_ADDRESS("glGenTextures");
        m_DeleteTextures = (void(*)(GLsizei,const GLuint*))GET_PROC_ADDRESS("glDeleteTextures");
        m_BindTexture = (void(*)(GLenum,GLuint))GET_PROC_ADDRESS("glBindTexture");
        m_TexParameteri = (void(*)(GLenum,GLenum,GLint))GET_PROC_ADDRESS("glTexParameteri");
        m_TexImage2D = (void(*)(GLenum,GLint,GLint,GLsizei,GLsizei,GLint,GLenum,GLenum,const void*))GET_PROC_ADDRESS("glTexImage2D");
        m_TexImage3D = (void(*)(GLenum,GLsizei,GLenum,GLsizei,GLsizei,GLsizei))GET_PROC_ADDRESS("glTexImage3D");
        m_TexSubImage3D = (void(*)(GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLenum,const void*))GET_PROC_ADDRESS("glTexSubImage3D");
        m_TexStorage3D = (void(*)(GLenum,GLsizei,GLenum,GLsizei,GLsizei,GLsizei))GET_PROC_ADDRESS("glTexStorage3D");

        m_GenVertexArrays = (void(*)(GLsizei,GLuint*))GET_PROC_ADDRESS("glGenVertexArrays");
        m_GenBuffers = (void(*)(GLsizei,GLuint*))GET_PROC_ADDRESS("glGenBuffers");
        m_BindVertexArray = (void(*)(GLuint))GET_PROC_ADDRESS("glBindVertexArray");
        m_BindBuffer = (void(*)(GLenum,GLuint))GET_PROC_ADDRESS("glBindBuffer");
        m_BufferData = (void(*)(GLenum,GLsizeiptr,const void*,GLenum))GET_PROC_ADDRESS("glBufferData");
        m_BufferSubData = (void(*)(GLenum,GLintptr,GLsizeiptr,const void*))GET_PROC_ADDRESS("glBufferSubData");
        m_VertexAttribPointer = (void(*)(GLuint,GLint,GLenum,GLboolean,GLsizei,const void*))GET_PROC_ADDRESS("glVertexAttribPointer");
        m_EnableVertexAttribArray = (void(*)(GLuint))GET_PROC_ADDRESS("glEnableVertexAttribArray");
        m_DeleteVertexArrays = (void(*)(GLsizei,const GLuint*))GET_PROC_ADDRESS("glDeleteVertexArrays");
        m_DeleteBuffers = (void(*)(GLsizei,const GLuint*))GET_PROC_ADDRESS("glDeleteBuffers");

        m_DrawElements = (void(*)(GLenum,GLsizei,GLenum,const void*))GET_PROC_ADDRESS("glDrawElements");
    }
}