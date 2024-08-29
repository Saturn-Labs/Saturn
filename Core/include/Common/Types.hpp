#pragma once
#include <functional>
#include <memory>
#include <optional>
#include <string>

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
    typedef std::string String;
    typedef std::wstring WString;
    typedef const char* CString;

    template<typename T>
    using Atomic = std::atomic<T>;

    template<typename T>
    using Function = std::function<T>;

    template<typename T>
    using Nullable = std::optional<T>;
    template<typename T>
    constexpr Nullable<T> CreateNullable(T value) {
        return std::optional<T>(value);
    }
    inline std::nullopt_t null = std::nullopt;

    template<typename T>
    using Vector = std::vector<T>;

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

