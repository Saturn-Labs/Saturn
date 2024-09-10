#pragma once
#include <type_traits>
#include <glad/gl.h>

namespace Saturn {
    template<GLenum>
    struct GLToCppType;

    // Specializations for each OpenGL type
    template<>
    struct GLToCppType<GL_FLOAT> {
        using type = float;
    };

    template<>
    struct GLToCppType<GL_DOUBLE> {
        using type = double;
    };

    template<>
    struct GLToCppType<GL_HALF_FLOAT> {
        using type = unsigned short;  // OpenGL doesn't have native support for half-float, use 16-bit int
    };

    template<>
    struct GLToCppType<GL_INT> {
        using type = int;
    };

    template<>
    struct GLToCppType<GL_UNSIGNED_INT> {
        using type = unsigned int;
    };

    template<>
    struct GLToCppType<GL_SHORT> {
        using type = short;
    };

    template<>
    struct GLToCppType<GL_UNSIGNED_SHORT> {
        using type = unsigned short;
    };

    template<>
    struct GLToCppType<GL_BYTE> {
        using type = signed char;
    };

    template<>
    struct GLToCppType<GL_UNSIGNED_BYTE> {
        using type = unsigned char;
    };

    template<>
    struct GLToCppType<GL_FIXED> {
        using type = int;  // GL_FIXED is represented as an int, but this is platform dependent
    };

    template<>
    struct GLToCppType<GL_BOOL> {
        using type = bool;
    };

    // Usage example:
    template<GLenum glType>
    using CppType = typename GLToCppType<glType>::type;

    class GLTypeHelper {
    public:
        template<typename T>
        static constexpr GLenum GetGLTypeForT() {
            if constexpr (std::is_same_v<T, float>) {
                return GL_FLOAT;
            } else if constexpr (std::is_same_v<T, double>) {
                return GL_DOUBLE;
            } else if constexpr (std::is_same_v<T, int>) {
                return GL_INT;
            } else if constexpr (std::is_same_v<T, unsigned int>) {
                return GL_UNSIGNED_INT;
            } else if constexpr (std::is_same_v<T, short>) {
                return GL_SHORT;
            } else if constexpr (std::is_same_v<T, unsigned short>) {
                return GL_UNSIGNED_SHORT;
            } else if constexpr (std::is_same_v<T, char>) {
                return GL_BYTE;
            } else if constexpr (std::is_same_v<T, unsigned char>) {
                return GL_UNSIGNED_BYTE;
            } else if constexpr (std::is_same_v<T, signed char>) {
                return GL_BYTE;  // Same as char, depending on platform
            } else if constexpr (std::is_same_v<T, unsigned long>) {
                return GL_UNSIGNED_INT;  // OpenGL does not differentiate long from int in many cases
            } else if constexpr (std::is_same_v<T, long>) {
                return GL_INT;  // Same reason, no direct GL_LONG
            } else if constexpr (std::is_same_v<T, long long>) {
                return GL_INT;  // OpenGL doesn't have long long support directly
            } else if constexpr (std::is_same_v<T, unsigned long long>) {
                return GL_UNSIGNED_INT;  // Similar limitation
            } else if constexpr (std::is_same_v<T, bool>) {
                return GL_BOOL;
            } else {
                static_assert(std::is_void_v<T>, "Unsupported type for OpenGL.");
            }
        }
    };
}
