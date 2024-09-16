#pragma once
#include <string>

namespace Saturn {
    class Shader;
    class GenericUniform {
    protected:
        std::string mName;
    public:
        explicit GenericUniform(const std::string& name) :
            mName(name) {
        }

        virtual ~GenericUniform() = default;
        virtual void UploadUniform(Shader& shader) = 0;
        std::string GetName() const {
            return mName;
        }
    };
}