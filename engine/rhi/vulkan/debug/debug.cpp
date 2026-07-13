module sonora.engine.rhi.vulkan.debug;
namespace sonora::engine::rhi::vulkan
{
    vk::Bool32 VkDebugUtils::DebugCallback(vk::DebugUtilsMessageSeverityFlagBitsEXT      severity,
                                           vk::DebugUtilsMessageTypeFlagsEXT             type,
                                           const vk::DebugUtilsMessengerCallbackDataEXT *pCallbackData,
                                           void *)
    {
        std::string prefix = "[Vulkan]";

        if (severity & vk::DebugUtilsMessageSeverityFlagBitsEXT::eError)
            prefix = "[Vulkan Error]";
        else if (severity & vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning)
            prefix = "[Vulkan Warning]";
        else if (severity & vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo)
            prefix = "[Vulkan Info]";
        else if (severity & vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose)
            prefix = "[Vulkan Verbose]";

        std::cerr << prefix << " " << pCallbackData->pMessage << std::endl;

        return vk::False;
    }

    void VkDebugUtils::PopulateDebugMessengerCreateInfo(vk::DebugUtilsMessengerCreateInfoEXT &createInfo)
    {
        createInfo = {
            .sType           = vk::StructureType::eDebugUtilsMessengerCreateInfoEXT,
            .messageSeverity = vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning
                               | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError,
            .messageType = vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation
                           | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance,
            .pfnUserCallback = DebugCallback
        };
    }
}  // namespace sonora::engine::rhi::vulkan