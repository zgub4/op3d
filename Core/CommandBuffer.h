#pragma once

#include "Device.h"
#include "VDeleter.h"
#include "Surface.h"

namespace op3d
{
    class CommandBuffer
    {
    public:
        CommandBuffer(const Device& device);
        VkCommandBuffer beginSingleTimeCommands();
        void endSingleTimeCommands(VkCommandBuffer commandBuffer, VkQueue graphicsQueue);

        void createCommandPool(const VkPhysicalDevice& physicalDevice, const Surface& surface);

        VkCommandPool getCommandPool() const { return commandPool; }

    private:
        const Device& device;
        VDeleter<VkCommandPool> commandPool;
    };
}

