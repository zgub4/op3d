#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <array>
#include <set>
#include <string.h>

#include "Vertex.h"
#include "VDeleter.h"
#include "Instance.h"
#include "Surface.h"
#include "PhysicalDevice.h"
#include "Device.h"
#include "DebugCallback.h"
#include "CommandBuffer.h"
#include "DescriptorSet.h"
#include "DescriptorPool.h"

#include "IO.h"
#include "UniformBufferObject.h"

const int WIDTH = 800;
const int HEIGHT = 600;

const std::vector<op3d::Vertex> vertices = {
    {{-0.5f, -0.5f, 0.0f},{1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    {{0.5f, -0.5f, 0.0f},{0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    {{0.5f, 0.5f, 0.0f},{0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
    {{-0.5f, 0.5f, 0.0f},{1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},

    { { -0.5f, -0.5f, -0.5f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f } },
    { { 0.5f, -0.5f, -0.5f },{ 0.0f, 1.0f, 0.0f },{ 1.0f, 0.0f } },
    { { 0.5f, 0.5f, -0.5f },{ 0.0f, 0.0f, 1.0f },{ 1.0f, 1.0f } },
    { { -0.5f, 0.5f, -0.5f },{ 1.0f, 1.0f, 1.0f },{ 0.0f, 1.0f } }
};

const std::vector<uint16_t> indices = {
    0, 1, 2, 2, 3, 0,
    4, 5, 6, 6, 7, 4
};


namespace op3d
{
    class Engine
    {
    public:
        void run();

    private:
        void initWindow();
        void initVulkan();
        void mainLoop();

        static void onWindowResized(GLFWwindow* window, int width, int height);
        void recreateSwapChain();
        void createRenderPass();
        void createDescriptorSetLayout();
        void createGraphicsPipeline();
        void createFramebuffers();
        void createDepthResources();
        void createTextureImage();
        void createTextureImageView();
        void createTextureSampler();

        void createImage(uint32_t width,
                         uint32_t height,
                         VkFormat format,
                         VkImageTiling tiling,
                         VkImageUsageFlags usage,
                         VkMemoryPropertyFlags properties,
                         VDeleter<VkImage>& image,
                         VDeleter<VkDeviceMemory>& imageMemory);

        void transitionImageLayout(VkImage image,
                                   VkFormat format,
                                   VkImageLayout oldLayout,
                                   VkImageLayout newLayout);

        void copyImage(VkImage srcImage, VkImage dstImage, uint32_t width, uint32_t height);
        void createImageView(VkImage image,
                             VkFormat format,
                             VkImageAspectFlags aspectFlags,
                             VDeleter<VkImageView>& imageView);

        void createVertexBuffer();
        void createIndexBuffer();
        void createUniformBuffer();

        void createBuffer(VkDeviceSize size,
                          VkBufferUsageFlags usage,
                          VkMemoryPropertyFlags properties,
                          VDeleter<VkBuffer>& buffer,
                          VDeleter<VkDeviceMemory>& bufferMemory);

        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

        VkFormat findDepthFormat();
        VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates,
                                     VkImageTiling tiling,
                                     VkFormatFeatureFlags features);

        bool hasStencilComponent(VkFormat format);

        void createCommandBuffers();
        void createSemaphores();
        void updateUniformBuffer();
        void drawFrame();

        void createShaderModule(const std::vector<char>& code, VDeleter<VkShaderModule>& shaderModule);

        GLFWwindow* window{ nullptr };

        Instance        instance{ vkDestroyInstance };
        DebugCallback   callback{ instance, DestroyDebugReportCallbackEXT };
        Surface         surface{ instance, vkDestroySurfaceKHR };
        PhysicalDevice  physicalDevice;
        Device          device{ vkDestroyDevice };

        VkQueue graphicsQueue{ VK_NULL_HANDLE };
        VkQueue presentQueue{ VK_NULL_HANDLE };

        SwapChain swapChain{ device,vkDestroySwapchainKHR };
        std::vector<VDeleter<VkImageView>> swapChainImageViews;
        std::vector<VDeleter<VkFramebuffer>> swapChainFramebuffers;

        VDeleter<VkRenderPass> renderPass{ device, vkDestroyRenderPass };
        VDeleter<VkDescriptorSetLayout> descriptorSetLayout{ device, vkDestroyDescriptorSetLayout };
        VDeleter<VkPipelineLayout> pipelineLayout{ device, vkDestroyPipelineLayout };
        VDeleter<VkPipeline> graphicsPipeline{ device, vkDestroyPipeline };

        CommandBuffer commandBufferManager{ device };

        VDeleter<VkImage> textureImage{ device, vkDestroyImage };
        VDeleter<VkDeviceMemory> textureImageMemory{ device, vkFreeMemory };
        VDeleter<VkImageView> textureImageView{ device, vkDestroyImageView };
        VDeleter<VkSampler> textureSampler{ device, vkDestroySampler };

        VDeleter<VkImage> depthImage{ device, vkDestroyImage };
        VDeleter<VkDeviceMemory> depthImageMemory{ device, vkFreeMemory };
        VDeleter<VkImageView> depthImageView{ device, vkDestroyImageView };

        VDeleter<VkBuffer> vertexBuffer{ device, vkDestroyBuffer };
        VDeleter<VkDeviceMemory> vertexBufferMemory{ device, vkFreeMemory };
        VDeleter<VkBuffer> indexBuffer{ device, vkDestroyBuffer };
        VDeleter<VkDeviceMemory> indexBufferMemory{ device, vkFreeMemory };

        VDeleter<VkBuffer> uniformStagingBuffer{ device, vkDestroyBuffer };
        VDeleter<VkDeviceMemory> uniformStagingBufferMemory{ device, vkFreeMemory };
        VDeleter<VkBuffer> uniformBuffer{ device, vkDestroyBuffer };
        VDeleter<VkDeviceMemory> uniformBufferMemory{ device, vkFreeMemory };

        DescriptorSet descriptorSet;
        DescriptorPool descriptorPool{ device };

        std::vector<VkCommandBuffer> commandBuffers;

        VDeleter<VkSemaphore> imageAvailableSemaphore{ device, vkDestroySemaphore };
        VDeleter<VkSemaphore> renderFinishedSemaphore{ device, vkDestroySemaphore };
    };
}
