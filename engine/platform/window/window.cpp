module sonora.engine.platform.window;
import sonora.engine.core.engine_definitions;
namespace sonora::engine::platform
{
    struct Window::Impl
    {
        GLFWwindow* window_ = nullptr;
        bool resized_ = false;
    };

    Window::Window() : impl_{std::make_unique<Impl>()}
    {
    }

    Window::~Window()
    {
        Destroy();
    }

    std::expected<void, std::string> Window::Initialize(const WindowDescription& description)
    {
        if (!glfwInit())
            return std::unexpected(
                std::string(sonora::engine::core::constants::EngineDefinitions::WINDOW_INIT_ERROR));

        glfwWindowHint(glfw::ClientApi, glfw::NoApi);

        impl_->window_ = glfwCreateWindow(description.width, description.height, description.title.c_str(),
                                          nullptr, nullptr);

        if (!impl_->window_) {
            glfwTerminate();
            return std::unexpected(
                std::string(sonora::engine::core::constants::EngineDefinitions::WINDOW_INIT_ERROR));
        }

        glfwSetWindowUserPointer(impl_->window_, impl_.get());

        glfwSetFramebufferSizeCallback(impl_->window_, [](GLFWwindow* window, int, int) {
            auto* impl = static_cast<Impl*>(glfwGetWindowUserPointer(window));

            if (impl) {
                impl->resized_ = true;
            }
        });

        return {};
    }

    void Window::PollEvents()
    {
        glfwPollEvents();
    }

    bool Window::ShouldClose() const
    {
        return glfwWindowShouldClose(impl_->window_);
    }

    GLFWwindow* Window::GetGlfwWindowPtr() const
    {
        return impl_->window_;
    }

    WindowSize Window::GetFramebufferSize() const
    {
        WindowSize size{};

        glfwGetFramebufferSize(impl_->window_, &size.width, &size.height);

        return size;
    }

    bool Window::WasResized() const
    {
        return impl_->resized_;
    }

    void Window::ResetResizedFlag()
    {
        impl_->resized_ = false;
    }

    void Window::Destroy()
    {
        if (impl_ && impl_->window_) {
            glfwDestroyWindow(impl_->window_);
            glfwTerminate();
        }
    }
} // namespace sonora::engine::platform