#include "Core/Content/DeferredContent.hpp"
#include <spdlog/fmt/bundled/format.h>

namespace Saturn {
    DeferredContent::DeferredContent(const Map<String, String>& filePaths) :
        mFilePaths(filePaths) {
    }

    DeferredContent::~DeferredContent() = default;

    bool DeferredContent::WaitUntilLoaded(UInt32 timeout) {
        const auto time = std::chrono::high_resolution_clock::now();
        while (true) {
            if (mContentState == ContentState::Failed || mContentState == ContentState::Loaded || (std::chrono::high_resolution_clock::now() - time) < std::chrono::milliseconds(timeout))
                break;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

        return mContentState == ContentState::Loaded;
    }

    ContentState DeferredContent::GetContentState() const {
        return mContentState;
    }

    bool DeferredContent::IsLoaded() const {
        return mContentState == ContentState::Loaded;
    }

    Nullable<Exception> DeferredContent::GetLoadingError() const {
        return mLoadingError;
    }

    const Map<String, String>& DeferredContent::GetFilePaths() const {
        return mFilePaths;
    }

    String DeferredContent::BuildAssetIdentifier(ContentType contentType, const Map<String, String>& filePaths) {
        String formatId;
        for (const auto& [sourceId, path] : filePaths)
            formatId += fmt::format("\"{}\":\"{}\",", sourceId, path);
        formatId.pop_back(); // Remove trailing ','
        return fmt::format("{}[{}]", ContentTypeName(contentType), formatId);
    }

    String DeferredContent::ContentTypeName(ContentType type) {
        switch (type) {
        case ContentType::ShaderContent:
            return "ShaderContent";
        case ContentType::UnknownContent:
            return "UnknownContent";
        default:
            return "DeferredContent";
        }
    }
}
