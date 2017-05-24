#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
namespace op3d
{
    template<typename T>
    class VObject
    {
    public:
        virtual ~VObject() = default;
        virtual operator const T &() const = 0;
        virtual operator T () const = 0;
        virtual const T* operator &() const = 0;
    };
}
