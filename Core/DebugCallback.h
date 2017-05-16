#pragma once

#include "VDeleter.h"
#include "ValidationLayers.h"

VkResult CreateDebugReportCallbackEXT(VkInstance instance,
                                      const VkDebugReportCallbackCreateInfoEXT* pCreateInfo,
                                      const VkAllocationCallbacks* pAllocator,
                                      VkDebugReportCallbackEXT* pCallback);

void DestroyDebugReportCallbackEXT(VkInstance instance,
                                   VkDebugReportCallbackEXT callback,
                                   const VkAllocationCallbacks* pAllocator);

namespace op3d
{
    class DebugCallback : public VDeleter<VkDebugReportCallbackEXT>
    {
    public:
        using VDeleter<VkDebugReportCallbackEXT>::VDeleter;
        void setup(const VkInstance& instance);

    private:
        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags,
                                                            VkDebugReportObjectTypeEXT objType,
                                                            uint64_t obj,
                                                            std::size_t location,
                                                            int32_t code,
                                                            const char* layerPrefix,
                                                            const char* msg,
                                                            void* userData);
    };
}

