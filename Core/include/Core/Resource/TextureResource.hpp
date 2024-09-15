#pragma once
#include "Core/Rendering/TextureData.hpp"
#include "Resource.hpp"

namespace Saturn {
    class TextureResource final : public Resource {
        std::string mTexturePath = "";
        std::shared_ptr<TextureData> mTextureData = {};
    public:
        TextureResource(ResourceManager &manager, const ResourceLocation &location);
        ~TextureResource() override;
        bool HasTextureData() const;
        std::shared_ptr<TextureData> GetTextureData() const;

    protected:
        void Load() override;
        void Unload() override;
    };
}