// TODO: specify binding index at pushing (desc_set2->injectBinding(uniform_block0, 0))?



#ifndef __RDTY_WRAPPERS_DESCRIPTOR_SET__
#define __RDTY_WRAPPERS_DESCRIPTOR_SET__



#include <vector>

#include "wrappers/src/base/base.h"
#include "wrappers/src/uniform-block/uniform-block.h"



namespace RDTY::WRAPPERS
{
	struct DescriptorSet : public Base
	{
		std::vector<UniformBlock*> bindings {};
	};
}



#endif
