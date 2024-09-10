#pragma once
#include "DeferredContent.hpp"
#include "Core/Rendering/Shader.hpp"

namespace Saturn {
    class ShaderContent final : public DeferredContent {
        String mVertexSource;
        String mFragmentSource;
        Shared<Shader> mCompiledShader;
    public:
        explicit ShaderContent(const Map<String, String>& filePaths);
        ~ShaderContent() override;
        void LoadContent() override;
        void UnloadContent() override;

        String GetVertexSource() const;
        String GetFragmentSource() const;
        Shared<Shader> Compile();

        CONTENT_TYPE(ShaderContent)
    };
}
