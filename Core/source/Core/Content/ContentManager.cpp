#include "Core/Content/ContentManager.hpp"
#include "Saturn.hpp"
#include "Core/Application.hpp"

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

    void ContentManager::PrintContentLoadingError(const String& assetIdentifier, const Exception& exception) {
        static const Logger& logger = Framework::GetCurrentApplication()->GetLogger();
        logger.Error("Failed to load content '{}': {}", assetIdentifier, exception.what());
    }
}
