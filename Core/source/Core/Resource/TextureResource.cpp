#include "Core/Resource/TextureResource.hpp"

namespace Saturn {
    TextureResource::TextureResource(ResourceManager &manager, const ResourceLocation &location) :
        Resource(manager, location) {
        if (!location.HasResourcePath())
            throw std::invalid_argument("A texture resource location needs to have the default 'resource' path!");
        mTexturePath = location.GetResourcePath();
    }

    TextureResource::~TextureResource() = default;

    bool TextureResource::HasTextureData() const { return mTextureData != nullptr; }
    std::shared_ptr<TextureData> TextureResource::GetTextureData() const { return mTextureData; }

    void TextureResource::Load() {
        if (HasTextureData())
            return;
        Int32 width;
        Int32 height;
        Int32 channels;
        const Byte *data = stbi_load(mTexturePath.c_str(), &width, &height, &channels, 0);
        mTextureData = std::make_shared<TextureData>(data, width, height, channels, TextureData::Allocator::STBI);
    }

    void TextureResource::Unload() { mTextureData.reset(); }
} // namespace Saturn
