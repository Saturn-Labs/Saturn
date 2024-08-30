#pragma once
#include "Timestep.hpp"
#include "Common/Types.hpp"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
namespace Saturn {
    class GLFWManager {
        static double s_LastUpdateTime;

    public:
        static void Initialize();
        static void Terminate();
        static void PollEvents();
        static void MakeContextCurrent(GLFWwindow* window);
        static void SetSwapInterval(int interval);
        static bool WindowShouldClose(GLFWwindow* window);
        static Timestep Update();
        static double GetTime();

        template<typename T>
        static T* GetWindowUserPointer(GLFWwindow* window) {
            return static_cast<T*>(glfwGetWindowUserPointer(window));
        }

        template<typename T>
        static void SetWindowUserPointer(GLFWwindow* window, T* pointer) {
            glfwSetWindowUserPointer(window, pointer);
        }

        static void SwapBuffers(GLFWwindow* window);
        static void SetWindowHint(int hint, int value);
        static GLFWwindow* CreateNewWindow(int width, int height, CString title, GLFWmonitor* monitor, GLFWwindow* share);
        static void DestroyWindow(GLFWwindow* window);
    };
}
