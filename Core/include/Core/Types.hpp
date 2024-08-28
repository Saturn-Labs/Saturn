#pragma once
#include <memory>

namespace Saturn {
    typedef float Single;
    typedef double Double;
    typedef char SByte;
    typedef short Int16;
    typedef int Int32;
    typedef long long Int64;
    typedef unsigned char Byte;
    typedef unsigned short UInt16;
    typedef unsigned int UInt32;
    typedef unsigned long long UInt64;

    template<typename T>
    using Shared = std::shared_ptr<T>;
    template<typename T, typename... Args>
    constexpr Shared<T> CreateShared(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Weak = std::weak_ptr<T>;
    template<typename T>
    constexpr Weak<T> GetWeak(Shared<T> ref)
    {
        return ref;
    }

    template<typename T>
    using Unique = std::unique_ptr<T>;
    template<typename T, typename... Args>
    constexpr Unique<T> CreateUnique(Args&&... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
}

