#pragma once

#include <vector>
#include <stdio.h>
#include <vector>
#include <set>

#include "SwapChainSupportDetails.h"
#include "QueueFamilyIndices.h"
#include "DeviceExtensions.h"
#include "VDeleter.h"
#include "SwapChain.h"

namespace op3d
{
    class PhysicalDevice
    {
    public:
        void create(const VkInstance& instance, const VkSurfaceKHR& surface);
        operator const VkPhysicalDevice&() const;

    private:
        static bool isDeviceSuitable(const VkPhysicalDevice& device, const VkSurfaceKHR& surface);
        static bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        static void printDeviceProperties(const VkPhysicalDevice& device);

        VkPhysicalDevice physicalDevice = nullptr;
    };
}
