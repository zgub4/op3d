#pragma once
#include "VObject.h"

namespace op3d
{
    class DescriptorSet : public VObject<VkDescriptorSet>
    {
    public:
        DescriptorSet();
        ~DescriptorSet();
        void createSet(const VkBuffer& uniformBuffer,
                       const VkImageView& textureImageView,
                       const VkSampler& textureSampler,
                       const VkDescriptorSetLayout& layout,
                       const VkDescriptorPool& pool,
                       const VkDevice& device);

        operator const VkDescriptorSet &() const override { return set; }
        operator VkDescriptorSet() const override { return set; }
        const VkDescriptorSet* operator &() const override { return &set; }

    private:
        VkDescriptorSet set;
    };
}

