#pragma once
#include <glm/vec4.hpp>


#include "LockableResource.hpp"
#include "TextureData.hpp"

namespace Saturn {
    enum class TextureFilter {
        Nearest = GL_NEAREST,
        Linear = GL_LINEAR,
        NearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST,
        LinearMipmapNearest = GL_LINEAR_MIPMAP_NEAREST,
        NearestMipmapLinear = GL_NEAREST_MIPMAP_LINEAR,
        Trilinear = GL_LINEAR_MIPMAP_LINEAR
    };

    enum class TextureWrap {
        Repeat           = GL_REPEAT,
        ClampToEdge      = GL_CLAMP_TO_EDGE,
        ClampToBorder    = GL_CLAMP_TO_BORDER,
        MirroredRepeat   = GL_MIRRORED_REPEAT
    };

    enum class TextureFormat {
        Red = GL_RED,
        RG = GL_RG,
        RGB = GL_RGB,
        RGBA = GL_RGBA
    };

    class Texture final : public LockableResource<UInt32, 0, UInt32> {
        std::shared_ptr<TextureData> mData = {};
        TextureFormat mFormat = TextureFormat::RGBA;
        TextureFilter mMinFilter = TextureFilter::Nearest;
        TextureFilter mMagFilter = TextureFilter::Nearest;
        TextureWrap mWrapS = TextureWrap::ClampToBorder;
        TextureWrap mWrapT = TextureWrap::ClampToBorder;
        glm::vec4 mBorderColor = {0.0, 0.0, 0.0, 0.0};
        Int32 mUnit = -1;
    public:
        Texture() = default;
        explicit Texture(const std::shared_ptr<TextureData> &data);
        Texture(const Texture &other) = delete;
        Texture &operator=(const Texture &other) = delete;
        Texture(Texture &&other) noexcept;
        Texture &operator=(Texture &&other) noexcept;
        ~Texture() override;
        void Lock(UInt32 unit) override;
        void Unlock() override;
        void SetFormat(TextureFormat format);
        TextureFormat GetFormat() const;
        void SetMinFilter(TextureFilter filter);
        TextureFilter GetMinFilter() const;
        void SetMagFilter(TextureFilter filter);
        TextureFilter GetMagFilter() const;
        void SetWrapS(TextureWrap wrapS);
        void SetWrapT(TextureWrap wrapT);
        TextureWrap GetWrapS() const;
        TextureWrap GetWrapT() const;
        void SetBorderColor(const glm::vec4 &borderColor);
        const glm::vec4 &GetBorderColor() const;
        void UpdateData() override;
        static UInt32 GetTextureUnits();
        static UInt32 GetActiveTextureUnit();
        static bool SetActiveTextureUnit(UInt32 unit);
        static bool LockTextureOnUnit(UInt32 texture, UInt32 unit);
        static UInt32 GetLockedTextureOnUnit(UInt32 unit);
    };
}