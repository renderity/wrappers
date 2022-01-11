// size_t
#include <cstddef>

#include "wrappers/src/descriptor-set/descriptor-set.h"



namespace RDTY
{
	namespace WRAPPERS
	{
		struct DescriptorSetOffsets
		{
			size_t bindings = offsetof(DescriptorSet, bindings);
		};

		DescriptorSetOffsets descriptor_set_offsets {};
	}
}
