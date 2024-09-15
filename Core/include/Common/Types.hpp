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
#include <exception>
#include <algorithm>
#include <ranges>
#include <filesystem>
#include <chrono>
namespace fs = std::filesystem;
#define GLFW_INCLUDE_NONE
#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/std.h"

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
    using namespace std::chrono_literals;
}

