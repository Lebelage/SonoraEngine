export module Sonora.Engine.Platform.Window;
import std;
import Sonora.Engine.ThirdParty.GLFW;
export namespace sonora::engine::platform
{
    struct WindowSize
    {
        int width = 0;
        int height = 0;
    };

    struct WindowDescription
    {
        int width = 0;
        int height = 0;
        std::string title;
    };

    class Window
    {
      public:
        explicit Window();
        ~Window();

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        Window(Window&&) noexcept = default;
        Window& operator=(Window&&) noexcept = default;

      public:
        std::expected<void, std::string> Initialize(const WindowDescription& desc);

        void PollEvents();
        void ResetResizedFlag();
        [[nodiscard]] bool ShouldClose() const;
        [[nodiscard]] bool WasResized() const;

        [[nodiscard]] GLFWwindow* GetGlfwWindowPtr() const;
        [[nodiscard]] WindowSize GetFramebufferSize() const;

      private:
        void Destroy();

      private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
    };

} // namespace sonora::engine::platform