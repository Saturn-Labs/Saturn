#pragma once
#include "Core/Rendering/LockableResource.hpp"
#include "Resource.hpp"

namespace Saturn {
    class Shader final : public Resource, public LockableResource<UInt32, 0> {
        bool mCompiled = false;
        std::string mVertexPath;
        std::string mFragmentPath;
    public:
        Shader(ResourceManager& manager, const ResourceLocation& location);
        ~Shader() override;
        bool IsCompiled() const;

    protected:
        void Load() override;
        void Unload() override;

    public:
        void Lock() override;
        void Unlock() override;
    };
}
