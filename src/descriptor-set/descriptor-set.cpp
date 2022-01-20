#include <cstddef> // size_t

#include "wrappers/src/descriptor-set/descriptor-set.h"



namespace RDTY::WRAPPERS
{
	struct DescriptorSetOffsets
	{
		size_t bindings = offsetof(DescriptorSet, bindings);
	};

	DescriptorSetOffsets descriptor_set_offsets {};
}
