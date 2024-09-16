#pragma once
#include "Core/Rendering/LockableResource.hpp"
#include "Core/Rendering/Shader/Shader.hpp"
#include "Resource.hpp"

namespace Saturn {
    class ShaderResource final : public Resource {
        std::string mVertexPath;
        std::string mFragmentPath;
        std::shared_ptr<Shader> mCompiledShader = {};
    public:
        ShaderResource(ResourceManager& manager, const ResourceLocation& location);
        ~ShaderResource() override;
        bool IsCompiled() const;
        std::shared_ptr<Shader> GetShader();

    protected:
        void Load() override;
        void Unload() override;
    };
}
