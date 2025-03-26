// #include "PhEngine/Graphics/GL.h"

// #define GET_PROC_ADDRESS SDL_GL_GetProcAddress

// #ifdef PHENGINE_DEBUG
// typedef void (APIENTRY *DEBUGPROC)(GLenum,GLenum,GLuint,GLenum,GLsizei,const GLchar*,const void*);
// #endif

// namespace PHENGINE_GRAPHICS_NAMESPACE
// {
// #ifdef PHENGINE_DEBUG
//     void APIENTRY opengl_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* user)
//     {
//         std::cerr << "OpenGL debug callback msg: " << message << '\n';
//     }
// #endif

//     GL::GL()
//     {
//         if (gladLoadGLContext(&m_GLADCtx, glfwGetProcAddress) == 0)
//         {
//             throw Exception("couldn't load OpenGL functions");
//         }

//     #ifdef PHENGINE_DEBUG
//         void (*m_Enable)(GLenum) = (void(*)(GLenum))GET_PROC_ADDRESS("glEnable");
//         void (*m_DebugMessageCallback)(DEBUGPROC,const void*) = (void(*)(DEBUGPROC,const void*))GET_PROC_ADDRESS("glDebugMessageCallback");
//         void (*m_DebugMessageControl)(GLenum,GLenum,GLenum,GLsizei,const GLuint*,GLboolean) = (void(*)(GLenum,GLenum,GLenum,GLsizei,const GLuint*,GLboolean))GET_PROC_ADDRESS("glDebugMessageControl");

//         m_Enable(0x92E0);
//         m_Enable(0x8242);
//         m_DebugMessageCallback(opengl_debug_callback, nullptr);
//         m_DebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
//     #endif
//     }
// }