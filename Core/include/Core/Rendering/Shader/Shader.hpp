#pragma once
#include "Core/Rendering/LockableResource.hpp"
#include "GenericUniform.hpp"
#include "Uniform.hpp"

namespace Saturn {
    class Shader final : public LockableResource<UInt32, 0> {
        std::unordered_map<std::string, Int32> mUniformCache = {};
        std::unordered_map<std::string, std::unique_ptr<GenericUniform>> mUniformList = {};
    public:
        Shader() = default;
        Shader(const std::string &vert, const std::string &frag);
        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;
        Shader(Shader &&other) noexcept;
        Shader &operator=(Shader &&other) noexcept;
        ~Shader() override;
        void Lock() override;
        void Unlock() override;
        void UpdateData() override;
        void UploadUniforms();
        template <typename T>
        void AddUniform(const std::string &name, T value) {
            mUniformList[name] = std::make_unique<Uniform<T>>(name, value);
        }

        template <typename T>
        std::optional<Uniform<T>&> GetUniform(const std::string &name) {
            const auto it = mUniformList.find(name);
            if (it == mUniformList.end())
                return std::nullopt;
            return *it->second;
        }
        bool HasUniform(const std::string &name) const;
        void RemoveUniform(const std::string &name);
        const std::unordered_map<std::string, Int32> &GetUniformCache() const;
        std::unordered_map<std::string, Int32> &GetUniformCache();
        static UInt32 Compile(const std::string &vert, const std::string &frag);
        static bool CheckShaderCompilation(UInt32 shader);
        static bool CheckProgramLinking(GLuint program);
        static UInt32 GetCurrentInUse();
        static bool UseProgram(UInt32 program);
    };
}