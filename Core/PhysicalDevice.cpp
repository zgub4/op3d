#include "PhysicalDevice.h"
#include "Surface.h"
#include "Device.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <algorithm>


void op3d::PhysicalDevice::create(const VkInstance& instance, const VkSurfaceKHR& surface)
{
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    printf("%d physical devices available in your system.\n", deviceCount);

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    for (const auto& device : devices)
    {
        if (isDeviceSuitable(device, surface))
        {
            printDeviceProperties(device);
            physicalDevice = device;
            break;
        }
    }
}

op3d::PhysicalDevice::operator const VkPhysicalDevice&() const
{
    return physicalDevice;
}

bool op3d::PhysicalDevice::isDeviceSuitable(const VkPhysicalDevice& device, const VkSurfaceKHR& surface)
{
    QueueFamilyIndices indices = QueueFamilyIndices::findQueueFamilies(device, surface);

    bool extensionsSupported = checkDeviceExtensionSupport(device);

    bool swapChainAdequate = false;
    if (extensionsSupported)
    {
        auto swapChainSupport = SwapChainSupportDetails::querySwapChainSupport(device, surface);
        swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
    }
    return indices.isComplete() && extensionsSupported && swapChainAdequate;
}

void op3d::PhysicalDevice::printDeviceProperties(const VkPhysicalDevice& device)
{
    VkPhysicalDeviceProperties deviceProperties = {};
    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    printf("physical device information:\n");
    printf("api version: %d\n", deviceProperties.apiVersion);
    printf("driver version: %d\n", deviceProperties.driverVersion);
    printf("vendor id: %d\n", deviceProperties.vendorID);
    printf("device id: %d\n", deviceProperties.deviceID);

    if (deviceProperties.deviceType == 1) { printf("device type: integrated gpu\n"); }
    else if (deviceProperties.deviceType == 2) { printf("device type: discrete gpu\n"); }
    else if (deviceProperties.deviceType == 3) { printf("device type: virtual gpu\n"); }
    else if (deviceProperties.deviceType == 4) { printf("device type: cpu\n"); }
    else { printf("device type: unknown\n"); }

    printf("pipeline cache uuid: %p\n", deviceProperties.pipelineCacheUUID);
    printf("device name: %s\n\n", deviceProperties.deviceName);
}

bool op3d::PhysicalDevice::checkDeviceExtensionSupport(VkPhysicalDevice device)
{
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

    std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

    for (const auto& extension : availableExtensions)
    {
        requiredExtensions.erase(extension.extensionName);
    }

    return requiredExtensions.empty();
}
