#pragma once
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <istream>
#include <fstream>
#include <future>
#include <ostream>
#include <thread>
#include <unordered_map>
#include <map>

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
    typedef uintptr_t UIntPtr;
    typedef intptr_t IntPtr;
    typedef std::string String;
    typedef std::wstring WString;
    typedef const char* CString;
    typedef std::exception Exception;

    template<typename T>
    using Atomic = std::atomic<T>;

    template<typename T>
    using Function = std::function<T>;

    template<typename T>
    using Future = std::future<T>;

    template<typename T>
    using Promise = std::promise<T>;

    template<typename T, typename... Args>
    using Async = std::future<std::invoke_result_t<T, Args...>>;

    template<typename T>
    using Nullable = std::optional<T>;
    template<typename T>
    constexpr Nullable<T> CreateNullable(T value) {
        return std::optional<T>(value);
    }
    inline std::nullopt_t null = std::nullopt;

    template<typename T>
    using Vector = std::vector<T>;
    typedef Vector<Byte> ByteArray;

    template<typename TKey, typename TValue>
    using Map = std::map<TKey, TValue>;

    template<typename TKey, typename TValue>
    using UnorderedMap = std::unordered_map<TKey, TValue>;

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

    using FileStream = std::fstream;
    using ReadFileStream = std::ifstream;
    using WriteFileStream = std::ofstream;
    using StringStream = std::stringstream;
    using Thread = std::thread;
    using namespace std::chrono_literals;
}

