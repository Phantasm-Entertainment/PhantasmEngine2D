#include "PhEngine/Graphics/Shader.h"

namespace PHENGINE_GRAPHICS_NAMESPACE
{
    void Shader::Use() const
    {
        m_GL->UseProgram(m_Program);
    }

    void Shader::SetUniform(const std::string& name, const Math::Vector2f& vec) const
    {
        GLint loc = m_GL->GetUniformLocation(m_Program, name.c_str());

        if (loc == -1)
        {
            throw Exception("invalid uniform '" + name + "'");
        }

        m_GL->Uniform2f(loc, vec.X, vec.Y);
    }

    std::shared_ptr<Shader> Shader::CreateShader(Window* win, const std::string& vss, const std::string& fss)
    {
        GladGLContext* gl = win->GetGraphicsDevice()->GetGL();
        int success;
        char log[1024];

        GLuint vs = gl->CreateShader(GL_VERTEX_SHADER);
        const char* vsSrc = vss.c_str();
        gl->ShaderSource(vs, 1, &vsSrc, NULL);
        gl->CompileShader(vs);
        gl->GetShaderiv(vs, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            gl->GetShaderInfoLog(vs, 1024, NULL, log);
            gl->DeleteShader(vs);
            std::string logStr = std::string("Couldn't compile vertex shader: ") + log;
            std::cerr << logStr << '\n';
            throw Exception(logStr);
        }

        GLuint fs = gl->CreateShader(GL_FRAGMENT_SHADER);
        const char* fsSrc = fss.c_str();
        gl->ShaderSource(fs, 1, &fsSrc, NULL);
        gl->CompileShader(fs);
        gl->GetShaderiv(fs, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            gl->GetShaderInfoLog(fs, 1024, NULL, log);
            gl->DeleteShader(vs);
            gl->DeleteShader(fs);
            std::string logStr = std::string("Couldn't compile fragment shader: ") + log;
            std::cerr << logStr << '\n';
            throw Exception(logStr);
        }

        GLuint program = gl->CreateProgram();
        gl->AttachShader(program, vs);
        gl->AttachShader(program, fs);
        gl->LinkProgram(program);
        gl->DeleteShader(vs);
        gl->DeleteShader(fs);
        gl->GetProgramiv(program, GL_LINK_STATUS, &success);

        if (!success)
        {
            gl->GetProgramInfoLog(program, 1024, NULL, log);
            gl->DeleteProgram(program);
            std::string logStr = std::string("Couldn't link shader program: ") + log;
            std::cerr << logStr << '\n';
            throw Exception(logStr);
        }

        return std::make_shared<Shader>(win, program);
    }
}