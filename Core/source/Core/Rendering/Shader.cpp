#include "Core/Rendering/Shader.hpp"

#include <glad/gl.h>
#include <spdlog/fmt/bundled/format.h>

namespace Saturn {
    Shader::Shader(const ShaderSource& source) {
        const CString vertexSrc = source.Vertex.c_str();
        const CString fragmentSrc = source.Fragment.c_str();

        const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexSrc, nullptr);
        glCompileShader(vertexShader);
        {
            GLint compileStatus;
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compileStatus);
            if (compileStatus == GL_FALSE) {
                GLint infoLogLength;
                glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLogLength);
                std::vector<char> infoLog(infoLogLength);
                glGetShaderInfoLog(vertexShader, infoLogLength, &infoLogLength, infoLog.data());
                glDeleteShader(vertexShader);
                throw Exception(fmt::format("Failed to compile vertex shader: {}", infoLog.data()).c_str());
            }
        }

        const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSrc, nullptr);
        glCompileShader(fragmentShader);
        {
            GLint compileStatus;
            glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compileStatus);
            if (compileStatus == GL_FALSE) {
                GLint infoLogLength;
                glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &infoLogLength);
                std::vector<char> infoLog(infoLogLength);
                glGetShaderInfoLog(fragmentShader, infoLogLength, &infoLogLength, infoLog.data());
                glDeleteShader(vertexShader);
                glDeleteShader(fragmentShader);
                throw Exception(fmt::format("Failed to compile fragment shader: {}", infoLog.data()).c_str());
            }
        }

        mIdentifier = glCreateProgram();
        if (mIdentifier == 0)
            throw Exception("Failed to create shader program!");

        glAttachShader(mIdentifier, vertexShader);
        glAttachShader(mIdentifier, fragmentShader);
        glLinkProgram(mIdentifier);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        {
            GLint linkStatus;
            glGetProgramiv(mIdentifier, GL_LINK_STATUS, &linkStatus);
            if (linkStatus == GL_FALSE) {
                GLint infoLogLength;
                glGetProgramiv(mIdentifier, GL_INFO_LOG_LENGTH, &infoLogLength);
                std::vector<char> infoLog(infoLogLength);
                glGetProgramInfoLog(mIdentifier, infoLogLength, &infoLogLength, infoLog.data());
                glDeleteProgram(mIdentifier);
                mIdentifier = 0;
                throw Exception(fmt::format("Failed to link shader program: {}", infoLog.data()).c_str());
            }
        }
    }

    Shader::Shader(Shader&& other) noexcept :
        mIdentifier(std::exchange(other.mIdentifier, 0)) {
    }

    Shader& Shader::operator=(Shader&& other) noexcept {
        if (this != &other)
            mIdentifier = std::exchange(other.mIdentifier, 0);
        return *this;
    }

    Shader::~Shader() {
        if (!IsValid())
            return;
        glDeleteProgram(mIdentifier);
        mIdentifier = 0;
    }

    void Shader::Use() const {
        if (!IsValid())
            return;
        glUseProgram(mIdentifier);
    }

    UInt32 Shader::GetIdentifier() const {
        return mIdentifier;
    }

    bool Shader::IsValid() const {
        return mIdentifier != 0;
    }

    void Shader::ResetSlot() {
        glUseProgram(0);
    }

    UInt32 Shader::GetCurrent() {
        Int32 currentProgram = 0;
        glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
        return static_cast<UInt32>(currentProgram);
    }
}
