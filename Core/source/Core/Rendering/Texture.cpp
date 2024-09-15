#include "Core/Rendering/Texture.hpp"

namespace Saturn {
    Texture::Texture(const std::shared_ptr<TextureData> &data) : mData(data) {
        glGenTextures(1, &mName);
        UpdateData();
    }

    Texture::Texture(Texture &&other) noexcept :
        mData(std::exchange(other.mData, {})), mFormat(std::exchange(other.mFormat, TextureFormat::RGBA)),
        mMinFilter(std::exchange(other.mMinFilter, TextureFilter::Nearest)),
        mMagFilter(std::exchange(other.mMagFilter, TextureFilter::Nearest)),
        mWrapS(std::exchange(other.mWrapS, TextureWrap::ClampToBorder)),
        mWrapT(std::exchange(other.mWrapT, TextureWrap::ClampToBorder)),
        mBorderColor(std::exchange(other.mBorderColor, {0.0, 0.0, 0.0, 0.0})), mUnit(std::exchange(other.mUnit, -1)) {
        mName = std::exchange(other.mName, 0);
    }

    Texture &Texture::operator=(Texture &&other) noexcept {
        if (this != &other) {
            mData = std::exchange(other.mData, {});
            mFormat = std::exchange(other.mFormat, TextureFormat::RGBA);
            mMinFilter = std::exchange(other.mMinFilter, TextureFilter::Nearest);
            mMagFilter = std::exchange(other.mMagFilter, TextureFilter::Nearest);
            mWrapS = std::exchange(other.mWrapS, TextureWrap::ClampToBorder);
            mWrapT = std::exchange(other.mWrapT, TextureWrap::ClampToBorder);
            mBorderColor = std::exchange(other.mBorderColor, {0.0, 0.0, 0.0, 0.0});
            mUnit = std::exchange(other.mUnit, -1);
            mName = std::exchange(other.mName, 0);
        }
        return *this;
    }

    Texture::~Texture() {
        if (!Texture::IsValid())
            return;
        glDeleteTextures(1, &mName);
    }

    void Texture::Lock(UInt32 unit) {
        if (SetActiveTextureUnit(unit)) {
            glBindTexture(GL_TEXTURE_2D, mName);
            mUnit = unit;
        }
    }

    void Texture::Unlock() {
        if (mUnit >= GetTextureUnits())
            return;
        const UInt32 lastActiveTextureUnit = GetActiveTextureUnit();
        if (SetActiveTextureUnit(mUnit)) {
            glBindTexture(GL_TEXTURE_2D, 0);
            SetActiveTextureUnit(lastActiveTextureUnit);
        }
    }

    void Texture::SetFormat(TextureFormat format) { mFormat = format; }
    TextureFormat Texture::GetFormat() const { return mFormat; }
    void Texture::SetMinFilter(TextureFilter filter) { mMinFilter = filter; }
    TextureFilter Texture::GetMinFilter() const { return mMinFilter; }
    void Texture::SetMagFilter(TextureFilter filter) { mMagFilter = filter; }
    TextureFilter Texture::GetMagFilter() const { return mMagFilter; }
    void Texture::SetWrapS(TextureWrap wrapS) { mWrapS = wrapS; }
    void Texture::SetWrapT(TextureWrap wrapT) { mWrapT = wrapT; }
    TextureWrap Texture::GetWrapS() const { return mWrapS; }
    TextureWrap Texture::GetWrapT() const { return mWrapT; }
    void Texture::SetBorderColor(const glm::vec4 &borderColor) { mBorderColor = borderColor; }
    const glm::vec4 &Texture::GetBorderColor() const { return mBorderColor; }

    void Texture::UpdateData() {
        if (!IsValid())
            return;

        const UInt32 lastActiveUnit = GetActiveTextureUnit();
        const UInt32 lastActiveTextureOnUnit0 = GetLockedTextureOnUnit(0);
        Lock(0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLenum>(mWrapS));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLenum>(mWrapT));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLenum>(mMagFilter));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLenum>(mMinFilter));
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, &mBorderColor[0]);
        if (mData && mData->IsValid()) {
            glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(mData->GetInternalFormat()), mData->GetWidth(),
                         mData->GetHeight(), 0, static_cast<GLenum>(GetFormat()), GL_UNSIGNED_BYTE, mData->GetData());
        }
        Unlock();
        LockTextureOnUnit(lastActiveTextureOnUnit0, 0);
        SetActiveTextureUnit(lastActiveUnit);
    }

    UInt32 Texture::GetTextureUnits() {
        Int32 units = 0;
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &units);
        return static_cast<UInt32>(units);
    }

    UInt32 Texture::GetActiveTextureUnit() {
        Int32 unit = 0;
        glGetIntegerv(GL_ACTIVE_TEXTURE, &unit);
        return static_cast<UInt32>(unit - GL_TEXTURE0);
    }

    bool Texture::SetActiveTextureUnit(UInt32 unit) {
        if (unit >= GetTextureUnits())
            return false;
        glActiveTexture(GL_TEXTURE0 + unit);
        return true;
    }

    bool Texture::LockTextureOnUnit(UInt32 texture, UInt32 unit) {
        if (unit >= GetTextureUnits())
            return false;
        SetActiveTextureUnit(unit);
        glBindTexture(GL_TEXTURE_2D, texture);
        return true;
    }

    UInt32 Texture::GetLockedTextureOnUnit(UInt32 unit) {
        if (unit >= GetTextureUnits())
            return 0;
        const UInt32 lastActiveUnit = GetActiveTextureUnit();
        SetActiveTextureUnit(unit);
        Int32 texture = 0;
        glGetIntegerv(GL_TEXTURE_BINDING_2D, &texture);
        SetActiveTextureUnit(lastActiveUnit);
        return static_cast<UInt32>(texture);
    }
}
