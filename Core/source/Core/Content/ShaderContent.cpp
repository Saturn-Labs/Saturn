#include "Core/Content/ShaderContent.hpp"

#include "Core/IO/File.hpp"

namespace Saturn {
    ShaderContent::ShaderContent(const Map<String, String>& filePaths) :
        DeferredContent(filePaths) {
        if (!filePaths.contains("vert") || !filePaths.contains("frag"))
            throw Exception("ShaderContent paths need at least 'vert' and 'frag'!");
    }

    ShaderContent::~ShaderContent() = default;

    void ShaderContent::LoadContent() {
        const String vertexFile = mFilePaths["vert"];
        const String fragmentFile = mFilePaths["frag"];
        mVertexSource = File::ReadAllText(vertexFile);
        mFragmentSource = File::ReadAllText(fragmentFile);
    }

    void ShaderContent::UnloadContent() {
        mVertexSource = "";
        mFragmentSource = "";
        mCompiledShader = nullptr;
    }

    String ShaderContent::GetVertexSource() const {
        return mVertexSource;
    }

    String ShaderContent::GetFragmentSource() const {
        return mFragmentSource;
    }

    Shared<Shader> ShaderContent::Compile() {
        if (GetContentState() != ContentState::Loaded)
            throw Exception("ShaderContent must be loaded before compiling!");
        if (mCompiledShader)
            return mCompiledShader;

        mCompiledShader = Shared<Shader>(new Shader({
            .Vertex = GetVertexSource(),
            .Fragment = GetFragmentSource()
        }));
        return mCompiledShader;
    }
}
