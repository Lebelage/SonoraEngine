module sonora.engine.rhi.vulkan.device;
import sonora.engine.core.logger;
namespace sonora::engine::rhi::vulkan
{
    using namespace sonora::engine::core;

    struct VkDevice::Impl
    {
        vk::raii::Context context_{};

        vk::raii::Instance               instance_        = nullptr;
        vk::raii::DebugUtilsMessengerEXT debug_messenger_ = nullptr;
    };

    VkDevice::VkDevice() : impl_(std::make_unique<Impl>()) {}

    VkDevice::~VkDevice()
    {
        Destroy();
    }

    void VkDevice::Destroy() {}

    void VkDevice::Initialize()
    {
        CreateInstance();
    }

    std::expected<void, std::string> VkDevice::CreateInstance()
    {
        constexpr vk::ApplicationInfo vk_application_info{
            .pApplicationName   = "SonoraEngine",
            .applicationVersion = vk::makeVersion(1, 0, 0),
            .pEngineName        = "Engine",
            .engineVersion      = vk::makeVersion(1, 0, 0),
            .apiVersion         = vk::ApiVersion14,
        };

        auto validation_layers_result = CheckValidationLayersSupport();

        if (enable_validation_layers_ && !validation_layers_result)
            return std::unexpected(validation_layers_result.error());

        auto required_extensions_result = GetRequiredExtensions();

        if (!required_extensions_result)
            return std::unexpected(required_extensions_result.error());

        vk::DebugUtilsMessengerCreateInfoEXT vk_debug_utils_messenger_create_info{};

        vk::InstanceCreateInfo vk_instance_create_info{
#ifdef __APPLE__
            .flags = vk::InstanceCreateFlagBits::eEnumeratePortabilityKHR,
#endif

            .pApplicationInfo        = &vk_application_info,
            .enabledLayerCount       = static_cast<uint32_t>(validation_layers_result.value().size()),
            .ppEnabledLayerNames     = validation_layers_result.value().data(),
            .enabledExtensionCount   = static_cast<uint32_t>(required_extensions_result.value().size()),
            .ppEnabledExtensionNames = required_extensions_result.value().data(),
        };

        impl_->instance_ = vk::raii::Instance(impl_->context_, vk_instance_create_info);

        return {};
    }

    std::expected<std::vector<const char *>, std::string> VkDevice::CheckValidationLayersSupport() const
    {
        std::vector<const char *> required_layers;

        if (enable_validation_layers_)
            required_layers.assign(validation_layers_.begin(), validation_layers_.end());

        auto layer_properties = impl_->context_.enumerateInstanceLayerProperties();

        const auto unsupported_it =
            std::ranges::find_if(required_layers,
                                 [&layer_properties](const auto &required_layer)
                                 {
                                     return std::ranges::none_of(layer_properties,
                                                                 [required_layer](const auto &layer_property)
                                                                 { return std::strcmp(layer_property.layerName, required_layer) == 0; });
                                 });

        if (unsupported_it != required_layers.end())
            return std::unexpected("Validation layer: " + std::string(*unsupported_it) + " is not supported");

        return required_layers;
    }

    std::expected<std::vector<const char *>, std::string> VkDevice::GetRequiredExtensions() const
    {
        std::uint32_t glfw_extensions_count = 0;

        auto glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extensions_count);

        auto extension_properties = impl_->context_.enumerateInstanceExtensionProperties();

        Logger::LogCollection(
            LogType::Info,
            "Available extension properties: ",
            extension_properties
                | std::views::transform([](const auto &extension_property) { return extension_property.extensionName.data(); })
                | std::ranges::to<std::vector<const char *>>());

        std::vector<const char *> extensions(glfw_extensions, glfw_extensions + glfw_extensions_count);

        for (std::size_t i = 0; i < glfw_extensions_count; ++i)
        {
            auto is_not_supported = std::ranges::none_of(extension_properties,
                                                         [glfw_extension = extensions[i]](const auto &extension_property)
                                                         { return std::strcmp(extension_property.extensionName, glfw_extension) == 0; });
            if (is_not_supported)
                return std::unexpected("Extension: " + std::string(extensions[i]) + " is not supported");
        }

        if (enable_validation_layers_)
            extensions.push_back(vk::EXTDebugUtilsExtensionName);

        extensions.push_back(vk::KHRGetPhysicalDeviceProperties2ExtensionName);
        extensions.push_back(vk::KHRPortabilityEnumerationExtensionName);

        return extensions;
    }
}  // namespace sonora::engine::rhi::vulkan
