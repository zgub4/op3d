#pragma once

#include <vector>
#include <string.h>

#include "VDeleter.h"
#include "ValidationLayers.h"

namespace op3d
{
    class Instance : public VDeleter<VkInstance>
    {
    public:
        using VDeleter<VkInstance>::VDeleter;
        void create();

    private:
        static bool checkValidationLayerSupport();
        static std::vector <const char*> getRequiredExtensions();
    };
}
