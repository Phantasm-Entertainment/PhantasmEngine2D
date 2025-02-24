#include "PhEngine/Graphics/GL.h"

#define GET_PROC_ADDRESS SDL_GL_GetProcAddress

namespace PHENGINE_GRAPHICS_NAMESPACE
{
    GL::GL()
    {
        m_ClearColor = (void(*)(GLfloat,GLfloat,GLfloat,GLfloat))GET_PROC_ADDRESS("glClearColor");
        m_Clear = (void(*)(GLbitfield))GET_PROC_ADDRESS("glClear");

        m_CreateShader = (GLuint(*)(GLenum))GET_PROC_ADDRESS("glCreateShader");
        m_DeleteShader = (void(*)(GLuint))GET_PROC_ADDRESS("glDeleteShader");
        m_ShaderSource = (void(*)(GLuint,GLsizei,const GLchar**,const GLint*))GET_PROC_ADDRESS("glShaderSource");
        m_CompileShader = (void(*)(GLuint))GET_PROC_ADDRESS("glCompileShader");

        m_GenTextures = (void(*)(GLsizei,GLuint*))GET_PROC_ADDRESS("glGenTextures");
        m_DeleteTextures = (void(*)(GLsizei,const GLuint*))GET_PROC_ADDRESS("glDeleteTextures");
        m_BindTexture = (void(*)(GLenum,GLuint))GET_PROC_ADDRESS("glBindTexture");
        m_TexParameteri = (void(*)(GLenum,GLenum,GLint))GET_PROC_ADDRESS("glTexParameteri");
        m_TexImage2D = (void(*)(GLenum,GLint,GLint,GLsizei,GLsizei,GLint,GLenum,GLenum,const void*))GET_PROC_ADDRESS("glTexImage2D");
        m_TexImage3D = (void(*)(GLenum,GLsizei,GLenum,GLsizei,GLsizei,GLsizei))GET_PROC_ADDRESS("glTexImage3D");
        m_TexSubImage3D = (void(*)(GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLenum,const void*))GET_PROC_ADDRESS("glTexSubImage3D");
        m_TexStorage3D = (void(*)(GLenum,GLsizei,GLenum,GLsizei,GLsizei,GLsizei))GET_PROC_ADDRESS("glTexStorage3D");
    }
}