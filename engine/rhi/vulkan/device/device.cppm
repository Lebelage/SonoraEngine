module;
#include <expected>
export module sonora.engine.rhi.vulkan.device;
import std;

import sonora.engine.core.engine_definitions;
import sonora.engine.third_party.glfw;

import vulkan;
export namespace sonora::engine::rhi::vulkan
{
#ifdef NDEBUG
    constexpr bool enable_validation_layers_ = false;
#else
    constexpr bool enable_validation_layers_ = true;
#endif

    class VkDevice
    {
    public:
        explicit VkDevice();
        ~VkDevice();

        VkDevice(const VkDevice&)            = delete;
        VkDevice& operator=(const VkDevice&) = delete;

        VkDevice(VkDevice&&)            = default;
        VkDevice& operator=(VkDevice&&) = default;

    public:
        void Initialize();
        void Destroy();

    public:
        [[nodiscard]] std::expected<std::vector<const char*>, std::string> CheckValidationLayersSupport() const;
        [[nodiscard]] std::expected<std::vector<const char*>, std::string> GetRequiredExtensions() const;

    private:
        std::expected<void, std::string> CreateInstance();

    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;

        const std::vector<const char*> validation_layers_ = {"VK_LAYER_KHRONOS_validation"};
    };
}  // namespace sonora::engine::rhi::vulkan