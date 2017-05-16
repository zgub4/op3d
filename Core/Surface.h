#pragma once

#include "VDeleter.h"

namespace op3d
{
    class Surface : public VDeleter<VkSurfaceKHR>
    {
    public:
        using VDeleter<VkSurfaceKHR>::VDeleter;
        void create(const VkInstance& instance, GLFWwindow* window);
    };
}
