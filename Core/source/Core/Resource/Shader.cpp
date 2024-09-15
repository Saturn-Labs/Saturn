#include "pch.hpp"
#include "Core/Resource/Shader.hpp"

#include "Core/Logger.hpp"
#include "Core/Exception/Exception.hpp"
#include "Core/IO/File.hpp"

namespace Saturn {
    Shader::Shader(ResourceManager& manager, const ResourceLocation& location) :
        Resource(manager, location) {
        if (!location.IsMultipleLocation())
            throw std::exception("Shader location must have multiple paths!");
        if (!location.HasPath("vertex") || !location.HasPath("fragment"))
            throw std::exception("Shader location must contain 'vertex' and 'fragment' paths!");

        mVertexPath = location.GetPath("vertex");
        mFragmentPath = location.GetPath("fragment");
    }

    Shader::~Shader() {
        if (IsCompiled())
            glDeleteShader(GetName());
    }

    bool Shader::IsCompiled() const { return mCompiled && IsValid(); }

    void Shader::Load() {
        if (IsCompiled())
            return;
        const std::string vertexSource = File::ReadAllText(mVertexPath);
        const std::string fragmentSource = File::ReadAllText(mFragmentPath);
        const char* vertCstr = vertexSource.c_str();
        const char* fragCstr = fragmentSource.c_str();

        const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertCstr, nullptr);
        glCompileShader(vertexShader);
        GLint vertexCompiled = false;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexCompiled);
        if (!vertexCompiled) {
            char infoLog[512];
            glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
            glDeleteShader(vertexShader);
            throw std::exception(std::format("Failed to compile vertex shader: {}", const_cast<const char*>(infoLog)).c_str());
        }

        const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragCstr, nullptr);
        glCompileShader(fragmentShader);
        GLint fragmentCompiled = false;
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentCompiled);
        if (!fragmentCompiled) {
            char infoLog[512];
            glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            throw std::exception(std::format("Failed to compile fragment shader: {}", const_cast<const char*>(infoLog)).c_str());
        }

        mName = glCreateProgram();
        glAttachShader(mName, vertexShader);
        glAttachShader(mName, fragmentShader);
        glLinkProgram(mName);
        GLint programLinked = false;
        glGetProgramiv(mName, GL_LINK_STATUS, &programLinked);
        if (!programLinked) {
            char infoLog[512];
            glGetProgramInfoLog(mName, 512, nullptr, infoLog);
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            glDeleteProgram(mName);
            mName = 0;
            throw std::exception(std::format("Failed to link shader program: {}", const_cast<const char*>(infoLog)).c_str());
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        mCompiled = true;
    }

    void Shader::Unload() {
        if (!IsCompiled())
            return;
        glDeleteProgram(GetName());
        mCompiled = false;
    }

    void Shader::Lock() {
        if (IsCompiled())
            glUseProgram(GetName());
    }

    void Shader::Unlock() {
        glUseProgram(0);
    }
}
