#pragma once
#include "Common/Types.hpp"

namespace Saturn {
    enum class TextureInternalFormat {
        Unknown = -1,
        R8 = GL_R8,
        RG8 = GL_RG8,
        RGB8 = GL_RGB8,
        RGBA8 = GL_RGBA8
    };

    class TextureData {
    public:
        enum class Allocator {
            Unknown = -1,
            STBI,
            OperatorNew
        };

    private:
        Byte* mData = nullptr;
        UInt32 mWidth = 0;
        UInt32 mHeight = 0;
        UInt32 mChannels = 0;
        Allocator mAllocator = Allocator::Unknown;

    public:
        TextureData();
        TextureData(UInt32 width, UInt32 height, UInt32 channels);
        TextureData(const Byte *data, UInt32 width, UInt32 height, UInt32 channels, Allocator allocator);
        TextureData(const TextureData& other) = delete;
        TextureData& operator=(const TextureData& other) = delete;
        TextureData(TextureData &&other) noexcept;
        TextureData &operator=(TextureData &&other) noexcept;
        ~TextureData();
        void DeleteData() const;
        bool IsValid() const;
        Byte *GetData() const;
        UInt32 GetWidth() const;
        UInt32 GetHeight() const;
        UInt32 GetChannels() const;
        TextureInternalFormat GetInternalFormat() const;
        void SetData(Byte *data, UInt32 width, UInt32 height, UInt32 channels, Allocator allocator);
        void SetData(const Byte *data, UInt32 width, UInt32 height, UInt32 channels, Allocator allocator);
        Allocator GetAllocator() const;
    };
}