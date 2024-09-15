#include "Core/Rendering/TextureData.hpp"

namespace Saturn {

    TextureData::TextureData() = default;
    TextureData::TextureData(UInt32 width, UInt32 height, UInt32 channels) :
        mWidth(width), mHeight(height), mChannels(channels), mAllocator(Allocator::OperatorNew) {
        mData = new Byte[mWidth * mHeight * mChannels];
        memset(mData, 0, mWidth * mHeight * mChannels);
    }

    TextureData::TextureData(const Byte *data, UInt32 width, UInt32 height, UInt32 channels, Allocator allocator) {
        SetData(data, width, height, channels, allocator);
    }

    TextureData::TextureData(TextureData &&other) noexcept :
        mData(std::exchange(other.mData, nullptr)),
        mWidth(std::exchange(other.mWidth, 0)),
        mHeight(std::exchange(other.mHeight, 0)),
        mChannels(std::exchange(other.mChannels, 0)),
        mAllocator(std::exchange(other.mAllocator, Allocator::Unknown)) {
    }

    TextureData &TextureData::operator=(TextureData &&other) noexcept {
        if (this != &other) {
            mData = std::exchange(other.mData, nullptr);
            mWidth = std::exchange(other.mWidth, 0);
            mHeight = std::exchange(other.mHeight, 0);
            mChannels = std::exchange(other.mChannels, 0);
            mAllocator = std::exchange(other.mAllocator, Allocator::Unknown);
        }
        return *this;
    }
    TextureData::~TextureData() { DeleteData(); }
    void TextureData::DeleteData() const {
        if (mData == nullptr)
            return;
        switch (mAllocator) {
        case Allocator::OperatorNew:
            delete[] mData;
            break;
        case Allocator::STBI:
            stbi_image_free(mData);
            break;
        default:
            break;
        }
    }

    bool TextureData::IsValid() const {
        return mData != nullptr && mWidth != 0 && mHeight != 0 && mChannels != 0 && mAllocator != Allocator::Unknown;
    }

    Byte *TextureData::GetData() const { return mData; }
    UInt32 TextureData::GetWidth() const { return mWidth; }
    UInt32 TextureData::GetHeight() const { return mHeight; }
    UInt32 TextureData::GetChannels() const { return mChannels; }

    TextureInternalFormat TextureData::GetInternalFormat() const {
        if (mChannels == 1) {
            return TextureInternalFormat::R8;
        }
        if (mChannels == 2) {
            return TextureInternalFormat::RG8;
        }
        if (mChannels == 3) {
            return TextureInternalFormat::RGB8;
        }
        if (mChannels == 4) {
            return TextureInternalFormat::RGBA8;
        }
        return TextureInternalFormat::Unknown;
    }

    void TextureData::SetData(Byte *data, UInt32 width, UInt32 height, UInt32 channels, Allocator allocator) {
        if (mData != nullptr) {
            DeleteData();
        }
        mData = data;
        mWidth = width;
        mHeight = height;
        mChannels = channels;
        mAllocator = allocator;
    }

    void TextureData::SetData(const Byte *data, UInt32 width, UInt32 height, UInt32 channels, Allocator allocator) {
        SetData(const_cast<Byte *>(data), width, height, channels, allocator);
    }

    TextureData::Allocator TextureData::GetAllocator() const {
        return mAllocator;
    }
}
