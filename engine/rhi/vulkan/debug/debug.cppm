export module sonora.engine.rhi.vulkan.debug;
import vulkan;
export namespace sonora::engine::rhi::vulkan
{
    class VkDebugUtils
    {
    public:
        static vk::Bool32 DebugCallback(vk::DebugUtilsMessageSeverityFlagBitsEXT      severity,
                                        vk::DebugUtilsMessageTypeFlagsEXT             type,
                                        const vk::DebugUtilsMessengerCallbackDataEXT *pCallbackData,
                                        void *);

        static void PopulateDebugMessengerCreateInfo(vk::DebugUtilsMessengerCreateInfoEXT &createInfo);
    };
}  // namespace sonora::engine::rhi::vulkan
