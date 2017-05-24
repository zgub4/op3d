#pragma once

#include <glm/glm.hpp>

namespace op3d
{
    class UniformBufferObject
    {
    public:
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 proj;
    };
}

