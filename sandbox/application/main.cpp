import sonora.engine.rhi.vulkan.device;
import std;
int main()
{
    std::cout << "Hello, Sonora Engine!" << std::endl;
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    sonora::engine::rhi::vulkan::VkDevice device;
    device.Initialize();
    return 0;
}