#include "pch.hpp"
#include "Core/Resource/ShaderResource.hpp"

#include "Core/Exception/Exception.hpp"
#include "Core/IO/File.hpp"
#include "Core/Logger.hpp"
#include "Core/Resource/ResourceManager.hpp"

namespace Saturn {
    ShaderResource::ShaderResource(ResourceManager& manager, const ResourceLocation& location) :
        Resource(manager, location) {
        if (!location.IsMultipleLocation())
            throw std::exception("Shader location must have multiple paths!");
        if (!location.HasPath("vertex") || !location.HasPath("fragment"))
            throw std::exception("Shader location must contain 'vertex' and 'fragment' paths!");

        mVertexPath = location.GetPath("vertex");
        mFragmentPath = location.GetPath("fragment");
    }

    ShaderResource::~ShaderResource() = default;

    bool ShaderResource::IsCompiled() const { return mCompiledShader != nullptr; }
    std::shared_ptr<Shader> ShaderResource::GetShader() {
        return mCompiledShader;
    }

    void ShaderResource::Load() {
        if (IsCompiled())
            return;
        const std::string vertexSource = File::ReadAllText(mVertexPath);
        const std::string fragmentSource = File::ReadAllText(mFragmentPath);
        mCompiledShader = std::make_shared<Shader>(vertexSource, fragmentSource);
    }

    void ShaderResource::Unload() {
        if (!IsCompiled())
            return;
        mCompiledShader.reset();
    }
}
