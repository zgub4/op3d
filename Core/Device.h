#pragma once

#include "VDeleter.h"

namespace op3d
{
    class Device : public VDeleter<VkDevice>
    {
    public:
        using VDeleter<VkDevice>::VDeleter;
        void create(const VkPhysicalDevice& physicalDevice,
                    const VkSurfaceKHR& surface,
                    VkQueue& graphicsQueue,
                    VkQueue& presentQueue);
    };
}
