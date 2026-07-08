module;
#include <GLFW/glfw3.h>

export module Sonora.Engine.ThirdParty.GLFW;

export using ::GLFWwindow;
export using ::glfwInit;
export using ::glfwTerminate;
export using ::glfwCreateWindow;
export using ::glfwDestroyWindow;
export using ::glfwWindowHint;
export using ::glfwPollEvents;
export using ::glfwWindowShouldClose;
export using ::glfwGetFramebufferSize;
export using ::glfwSetWindowUserPointer;
export using ::glfwGetWindowUserPointer;
export using ::glfwSetFramebufferSizeCallback;

export namespace sonora::engine::glfw
{
    constexpr int ClientApi = GLFW_CLIENT_API;
    constexpr int NoApi = GLFW_NO_API;

    enum class Key
    {
        Unknown = GLFW_KEY_UNKNOWN,
        Space = GLFW_KEY_SPACE,
        Escape = GLFW_KEY_ESCAPE,
        Enter = GLFW_KEY_ENTER,
        W = GLFW_KEY_W,
        A = GLFW_KEY_A,
        S = GLFW_KEY_S,
        D = GLFW_KEY_D
    };

    enum class Action
    {
        Release = GLFW_RELEASE,
        Press = GLFW_PRESS,
        Repeat = GLFW_REPEAT
    };
} // namespace sonora::engine::glfw