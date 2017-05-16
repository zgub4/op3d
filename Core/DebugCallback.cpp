#include "DebugCallback.h"
#include <iostream>

VkResult CreateDebugReportCallbackEXT(VkInstance instance,
                                      const VkDebugReportCallbackCreateInfoEXT* createInfo,
                                      const VkAllocationCallbacks* allocator,
                                      VkDebugReportCallbackEXT* callback)
{
    auto func = reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT"));
    if (func != nullptr)
    {
        return func(instance, createInfo, allocator, callback);
    }
    return VK_ERROR_EXTENSION_NOT_PRESENT;
}

void DestroyDebugReportCallbackEXT(VkInstance instance,
                                   VkDebugReportCallbackEXT callback,
                                   const VkAllocationCallbacks* allocator)
{
    auto func = reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT"));
    if (func != nullptr)
    {
        func(instance, callback, allocator);
    }
}

void op3d::DebugCallback::setup(const VkInstance& instance)
{
    if (!enableValidationLayers) return;

    VkDebugReportCallbackCreateInfoEXT createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
    createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
    createInfo.pfnCallback = debugCallback;

    if (CreateDebugReportCallbackEXT(instance, &createInfo, nullptr, replace()) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to set up debug callback!");
    }
}

VkBool32 op3d::DebugCallback::debugCallback(VkDebugReportFlagsEXT flags,
                                            VkDebugReportObjectTypeEXT objType,
                                            uint64_t obj,
                                            std::size_t location,
                                            int32_t code,
                                            const char* layerPrefix,
                                            const char* msg,
                                            void* userData)
{
    std::cerr << "validation layer: " << msg << std::endl;
    return VK_FALSE;
}
