import sonora.engine.rhi.vulkan.device;
import std;
int main()
{
    std::cout << "Hello, Sonora Engine!" << std::endl;

    sonora::engine::rhi::vulkan::VkDevice device;
    device.Initialize();
    return 0;
}