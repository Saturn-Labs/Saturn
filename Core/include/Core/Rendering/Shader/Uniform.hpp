#pragma once
#include <string>
#include "GenericUniform.hpp"

namespace Saturn {
    template <typename T>
    class Uniform final : public GenericUniform {
    protected:
        T mValue;

    public:
        Uniform(const std::string &name, T value);
        T GetValue() const;
        void UploadUniform(Shader &shader) override;
    };


    template <>
    class Uniform<float> final : public GenericUniform {
    protected:
        float mValue;

    public:
        Uniform(const std::string &name, float value);
        float GetValue() const;
        void UploadUniform(Shader &shader) override;
    };

    template <>
    class Uniform<int> final : public GenericUniform {
    protected:
        int mValue;

    public:
        Uniform(const std::string &name, int value);
        int GetValue() const;
        void UploadUniform(Shader &shader) override;
    };
}