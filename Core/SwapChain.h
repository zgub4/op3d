#pragma once

#include "VDeleter.h"

#include <vector>

#define GLFW_INCLUDE_VULKAN
#include <GLFW\glfw3.h>

#include "Device.h"
#include "Surface.h"
#include "PhysicalDevice.h"

namespace op3d 
{
    class SwapChain : public VDeleter<VkSwapchainKHR>
    {
    public:
        using VDeleter<VkSwapchainKHR>::VDeleter;
        void create(const Device& device, const Surface& surface, const VkPhysicalDevice& physicalDevice, GLFWwindow* window);
        void createImageViews(const Device& device, std::vector <VDeleter<VkImageView>>& imageViews);

        VkFormat getFormat() const { return imageFormat; }
        VkExtent2D getExtent() const { return extent; }

    private:
        void createImageView(const Device& device, VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, VDeleter<VkImageView>& imageView);

        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow* window);

        std::vector <VkImage> images;
        VkFormat imageFormat;
        VkExtent2D extent;
    };
}
