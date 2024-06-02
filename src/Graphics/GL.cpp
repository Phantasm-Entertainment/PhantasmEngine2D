#include "PhEngine/Graphics/GL.h"

#define GET_PROC_ADDRESS SDL_GL_GetProcAddress

namespace PHENGINE_GRAPHICS_NAMESPACE
{
    GL::GL()
    {
        m_ClearColor    = (void(*)(GLfloat,GLfloat,GLfloat,GLfloat))GET_PROC_ADDRESS("glClearColor");
        m_Clear         = (void(*)(GLbitfield))GET_PROC_ADDRESS("glClear");

        m_CreateShader  = (GLuint(*)(GLenum))GET_PROC_ADDRESS("glCreateShader");
        m_DeleteShader  = (void(*)(GLuint))GET_PROC_ADDRESS("glDeleteShader");
        m_ShaderSource  = (void(*)(GLuint,GLsizei,const GLchar**,const GLint*))GET_PROC_ADDRESS("glShaderSource");
        m_CompileShader = (void(*)(GLuint))GET_PROC_ADDRESS("glCompileShader");
    }
}