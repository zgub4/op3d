#pragma once
#include "VObject.h"

namespace op3d
{
    class DescriptorPool : public VObject<VkDescriptorPool>
    {
    public:
        DescriptorPool(const VkDevice& device);
        ~DescriptorPool();
        
        void createPool();

        operator const VkDescriptorPool &() const override { return pool; }
        operator VkDescriptorPool () const override { return pool; }
        const VkDescriptorPool* operator &() const override { return &pool; }

    private:
        const VkDevice& device;
        VkDescriptorPool pool;
    };
}
