#pragma once
#include "ContentType.hpp"
#include "Common/Types.hpp"

namespace Saturn {
    enum class ContentState : char {
        Unknown = -1,
        Unloaded,
        Loading,
        Loaded,
        Failed
    };

    class DeferredContent {
        friend class ContentManager;
    protected:
        ContentState mContentState = ContentState::Unloaded;
        Nullable<Exception> mLoadingError = null;
        Map<String, String> mFilePaths = {};

    public:
        explicit DeferredContent(const Map<String, String>& filePaths);
        virtual ~DeferredContent();
        virtual void LoadContent() = 0;
        virtual void UnloadContent() = 0;
        bool WaitUntilLoaded(UInt32 timeout = 4000);

        ContentState GetContentState() const;
        bool IsLoaded() const;
        Nullable<Exception> GetLoadingError() const;
        const Map<String, String>& GetFilePaths() const;

        static String BuildAssetIdentifier(ContentType contentType, const Map<String, String>& filePaths);
        static String ContentTypeName(ContentType type);
    };
}
