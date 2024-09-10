#include "Core/Content/ContentManager.hpp"

namespace Saturn {
    ContentManager::ContentManager(const String& contentPath) :
        mContentPath(contentPath) {
    }

    ContentManager::~ContentManager() = default;
    void ContentManager::UnloadContent(const String& assetIdentifier, bool eraseFromCache) {
        if (!mContentCache.contains(assetIdentifier))
            return;
        Shared<DeferredContent> content = mContentCache[assetIdentifier];
        if (content->GetContentState() != ContentState::Loaded)
            return;

        Future<void> asyncFuture = std::async(std::launch::async, [&content] {
            content->UnloadContent();
            content->mContentState = ContentState::Unloaded;
        });
        if (eraseFromCache)
            mContentCache.erase(assetIdentifier);
    }
}
