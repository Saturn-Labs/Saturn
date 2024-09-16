#include "Core/Rendering/Shader/Shader.hpp"

namespace Saturn {
    Shader::Shader(const std::string &vert, const std::string &frag) { mName = Compile(vert, frag); }
    Shader::Shader(Shader &&other) noexcept :
        mUniformCache(std::move(other.mUniformCache)), mUniformList(std::move(other.mUniformList)) {
        mName = std::exchange(other.mName, 0);
    }

    Shader &Shader::operator=(Shader &&other) noexcept {
        if (this != &other) {
            mUniformCache = std::move(other.mUniformCache);
            mUniformList = std::move(other.mUniformList);
            mName = std::exchange(other.mName, 0);
        }
        return *this;
    }

    Shader::~Shader() {
        if (!Shader::IsValid())
            return;
        glDeleteProgram(mName);
    }

    void Shader::Lock() {
        if (!IsValid())
            return;
        glUseProgram(mName);
    }

    void Shader::Unlock() { glUseProgram(0); }
    void Shader::UpdateData() {
        if (!IsValid())
            return;
        const UInt32 lastInUse = GetCurrentInUse();
        Lock();
        UploadUniforms();
        UseProgram(lastInUse);
    }

    void Shader::UploadUniforms() {
        for (const auto &uniform : mUniformList | std::views::values) {
            uniform->UploadUniform(*this);
        }
    }

    bool Shader::HasUniform(const std::string &name) const { return mUniformList.contains(name); }
    void Shader::RemoveUniform(const std::string &name) {
        if (!HasUniform(name))
            return;
        mUniformList.erase(name);
    }

    const std::unordered_map<std::string, Int32> &Shader::GetUniformCache() const { return mUniformCache; }
    std::unordered_map<std::string, Int32> &Shader::GetUniformCache() { return mUniformCache; }
    UInt32 Shader::Compile(const std::string &vert, const std::string &frag) {
        const char* vertexSrc = vert.c_str();
        const char* fragmentSrc = frag.c_str();
        const UInt32 vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexSrc, nullptr);
        glCompileShader(vertexShader);
        if (!CheckShaderCompilation(vertexShader)) {
            glDeleteShader(vertexShader);
            return 0;
        }

        const UInt32 fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSrc, nullptr);
        glCompileShader(fragmentShader);
        if (!CheckShaderCompilation(fragmentShader)) {
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            return 0;
        }

        const UInt32 shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        if (!CheckProgramLinking(shaderProgram)) {
            glDeleteProgram(shaderProgram);
            return 0;
        }
        return shaderProgram;
    }

    bool Shader::CheckShaderCompilation(UInt32 shader) {
        if (!shader)
            return false;
        std::string shaderTypeString = "unknown shader type";
        GLint shaderType = 0;
        glGetShaderiv(shader, GL_SHADER_TYPE, &shaderType);
        switch (shaderType) {
        case GL_VERTEX_SHADER:
            shaderTypeString = "vertex";
            break;
        case GL_FRAGMENT_SHADER:
            shaderTypeString = "fragment";
            break;
        default:
            shaderTypeString = "unknown";
            break;
        }

        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            GLchar infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            Logger::Error("Failed to compile {} shader: {}", shaderTypeString, const_cast<const char *>(infoLog));
            return false;
        }
        return true;
    }

    bool Shader::CheckProgramLinking(GLuint program) {
        if (!program)
            return false;
        GLint success;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            GLchar infoLog[512];
            glGetProgramInfoLog(program, 512, nullptr, infoLog);
            Logger::Error("Failed to link shader program: {}", const_cast<const char *>(infoLog));
            return false;
        }
        return true;
    }

    UInt32 Shader::GetCurrentInUse() {
        GLint currentProgram = 0;
        glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
        return static_cast<UInt32>(currentProgram);
    }

    bool Shader::UseProgram(UInt32 program) {
        if (program == 0)
            return false;
        glUseProgram(program);
        return true;
    }
}
