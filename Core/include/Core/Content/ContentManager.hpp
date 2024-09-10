#pragma once
#include <filesystem>
#include <ranges>

#include "DeferredContent.hpp"
#include "Common/Types.hpp"

namespace Saturn {
    class ContentManager {
        friend class Application;
    protected:
        String mContentPath;
        UnorderedMap<String, Shared<DeferredContent>> mContentCache;
        explicit ContentManager(const String& contentPath);
        ~ContentManager();

    public:
        template<class TContent, typename... ContentArgs>
        Shared<TContent> LoadContent(const Map<String, String>& filePaths, ContentArgs&&... contentArgs) {
            Map<String, String> completeFilePaths;
            for (auto&[id, path] : filePaths)
                completeFilePaths[id] = std::filesystem::path(mContentPath).concat(path).string();

            const String assetIdentifier = DeferredContent::BuildAssetIdentifier(TContent::GetContentType(), completeFilePaths);
            if (mContentCache.contains(assetIdentifier))
                return std::static_pointer_cast<TContent>(mContentCache[assetIdentifier]);

            Shared<TContent> content = CreateShared<TContent>(completeFilePaths, std::forward<ContentArgs>(contentArgs)...);
            mContentCache[assetIdentifier] = content;
            Future<void> asyncOperation = std::async(std::launch::async, [contentToLoad = mContentCache[assetIdentifier]] {
                contentToLoad->mContentState = ContentState::Loading;
                try {
                    contentToLoad->LoadContent();
                    contentToLoad->mLoadingError = null;
                    contentToLoad->mContentState = ContentState::Loaded;
                }
                catch (const std::exception& e) {
                    contentToLoad->mLoadingError = e;
                    contentToLoad->mContentState = ContentState::Failed;
                }
            });
            return content;
        }

        template<typename TContent, typename... ContentArgs>
        Shared<TContent> LoadContent(const String& filePath, ContentArgs&&... contentArgs) {
            return LoadContent<TContent>({{"asset_path", filePath}}, std::forward<ContentArgs>(contentArgs)...);
        }

        void UnloadContent(const String& assetIdentifier, bool eraseFromCache = true);
    };
}
