#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <stdexcept>
#include <functional>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <array>
#include <set>
#include "Vertex.h"
#include "VDeleter.h"
#include <string.h>

#include "Instance.h"
#include "Surface.h"
#include "PhysicalDevice.h"
#include "Device.h"
#include "DebugCallback.h"

#include "IO.h"

const int WIDTH = 800;
const int HEIGHT = 600;

struct UniformBufferObject
{
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
};

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
        void createSwapChain();
        void createImageViews();
        void createRenderPass();
        void createDescriptorSetLayout();
        void createGraphicsPipeline();
        void createFramebuffers();
        void createCommandPool();
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
        void createDescriptorPool();
        void createDescriptorSet();

        void createBuffer(VkDeviceSize size,
                          VkBufferUsageFlags usage,
                          VkMemoryPropertyFlags properties,
                          VDeleter<VkBuffer>& buffer,
                          VDeleter<VkDeviceMemory>& bufferMemory);

        VkCommandBuffer beginSingleTimeCommands();
        void endSingleTimeCommands(VkCommandBuffer commandBuffer);
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

        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);




        GLFWwindow* window{ nullptr };

        Instance instance{ vkDestroyInstance };
        DebugCallback callback{ instance, DestroyDebugReportCallbackEXT };
        Surface surface{ instance, vkDestroySurfaceKHR };
        PhysicalDevice physicalDevice;
        Device device{ vkDestroyDevice };

        VkQueue graphicsQueue{ VK_NULL_HANDLE };
        VkQueue presentQueue{ VK_NULL_HANDLE };

        VDeleter<VkSwapchainKHR> swapChain{ device, vkDestroySwapchainKHR };
        std::vector<VkImage> swapChainImages;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
        std::vector<VDeleter<VkImageView>> swapChainImageViews;
        std::vector<VDeleter<VkFramebuffer>> swapChainFramebuffers;

        VDeleter<VkRenderPass> renderPass{ device, vkDestroyRenderPass };
        VDeleter<VkDescriptorSetLayout> descriptorSetLayout{ device, vkDestroyDescriptorSetLayout };
        VDeleter<VkPipelineLayout> pipelineLayout{ device, vkDestroyPipelineLayout };
        VDeleter<VkPipeline> graphicsPipeline{ device, vkDestroyPipeline };

        VDeleter<VkCommandPool> commandPool{ device, vkDestroyCommandPool };

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

        VDeleter<VkDescriptorPool> descriptorPool{ device, vkDestroyDescriptorPool };
        VkDescriptorSet descriptorSet;

        std::vector<VkCommandBuffer> commandBuffers;

        VDeleter<VkSemaphore> imageAvailableSemaphore{ device, vkDestroySemaphore };
        VDeleter<VkSemaphore> renderFinishedSemaphore{ device, vkDestroySemaphore };
    };
}