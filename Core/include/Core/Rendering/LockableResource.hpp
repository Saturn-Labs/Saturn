#pragma once
#include "Core/Logger.hpp"
#include "GraphicsResource.hpp"

namespace Saturn {
    template<typename TName, TName NameInvalid, typename... LockArgs>
    class ResourceLock;

    template<typename TName, TName NameInvalid, typename... LockArgs>
    class LockableResource : public GraphicsResource<TName, NameInvalid> {
    public:
        LockableResource() = default;
        LockableResource(const LockableResource&) = delete;
        LockableResource(LockableResource&&) = delete;
        LockableResource& operator=(const LockableResource&) = delete;
        LockableResource& operator=(LockableResource&&) = delete;
        ~LockableResource() override = default;

        virtual void Lock(LockArgs...) = 0;
        virtual void Unlock() = 0;
        virtual void UpdateData() {}
        ResourceLock<TName, NameInvalid, LockArgs...> GetLock(LockArgs&&... lockArgs) {
            return ResourceLock<TName, NameInvalid, LockArgs...>(this, std::forward<LockArgs>(lockArgs)...);
        }
    };

    template<typename TName, TName NameInvalid, typename... LockArgs>
    class ResourceLock {
        LockableResource<TName, NameInvalid, LockArgs...>* mLockableResource = nullptr;
    public:
        ResourceLock() = delete;
        ResourceLock(const ResourceLock&) = delete;
        ResourceLock& operator=(const ResourceLock&) = delete;
        ResourceLock(ResourceLock&& other) noexcept :
            mLockableResource(std::exchange(other.mLockableResource, nullptr)) {
        }
        ResourceLock& operator=(ResourceLock&& other) noexcept {
            if (this != &other) {
                mLockableResource = std::exchange(other.mLockableResource, nullptr);
            }
            return *this;
        }
        explicit ResourceLock(LockableResource<TName, NameInvalid, LockArgs...>* lockableResource, LockArgs&&... args) :
            mLockableResource(lockableResource) {
            if (!lockableResource)
                throw std::invalid_argument("Lockable resource cannot be null");
            mLockableResource->Lock(std::forward<LockArgs>(args)...);
        }

        ~ResourceLock() {
            if (mLockableResource)
                mLockableResource->Unlock();
        }
    };
}