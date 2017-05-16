#include "Surface.h"
#include <stdexcept>


void op3d::Surface::create(const VkInstance& instance, GLFWwindow* window)
{
    if (glfwCreateWindowSurface(instance, window, nullptr, replace()) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create VkSurfaceKHR!");
    }
}
