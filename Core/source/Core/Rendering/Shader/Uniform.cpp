#include "Core/Rendering/Shader/Uniform.hpp"

#include "Core/Logger.hpp"
#include "Core/Rendering/Shader/Shader.hpp"

namespace Saturn {
    template <typename T>
    Uniform<T>::Uniform(const std::string &name, T value) :
        GenericUniform(name),
        mValue(value) {
    }

    template <typename T>
    T Uniform<T>::GetValue() const { return mValue; }

    template <typename T>
    void Uniform<T>::UploadUniform(Shader &shader) {
        Logger::Error("Not implemented for {}", typeid(T).name());
    }

    Uniform<float>::Uniform(const std::string &name, float value) :
        GenericUniform(name),
        mValue(value) {
    }

    float Uniform<float>::GetValue() const { return mValue; }
    void Uniform<float>::UploadUniform(Shader &shader) {
        auto &uniformCache = shader.GetUniformCache();
        Int32 uniformLocation = -1;
        if (!uniformCache.contains(mName)) {
            uniformLocation = glGetUniformLocation(shader.GetName(), mName.c_str());
            if (uniformLocation == -1) {
                Logger::Error("Failed to find the uniform '{}' on shader program {}!", mName, shader.GetName());
                return;
            }
            uniformCache[mName] = uniformLocation;
        } else
            uniformLocation = uniformCache[mName];
        glUniform1f(uniformLocation, mValue);
    }

    Uniform<int>::Uniform(const std::string &name, int value) :
        GenericUniform(name),
        mValue(value) {
    }

    int Uniform<int>::GetValue() const { return mValue; }
    void Uniform<int>::UploadUniform(Shader &shader) {
        auto &uniformCache = shader.GetUniformCache();
        Int32 uniformLocation = -1;
        if (!uniformCache.contains(mName)) {
            uniformLocation = glGetUniformLocation(shader.GetName(), mName.c_str());
            if (uniformLocation == -1) {
                Logger::Error("Failed to find the uniform '{}' on shader program {}!", mName, shader.GetName());
                return;
            }
            uniformCache[mName] = uniformLocation;
        } else
            uniformLocation = uniformCache[mName];
        glUniform1i(uniformLocation, mValue);
    }
} // namespace Saturn
