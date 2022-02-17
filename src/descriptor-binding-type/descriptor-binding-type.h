#ifndef __RDTY_WRAPPERS_DESCRIPTOR_BINDING_TYPE__
#define __RDTY_WRAPPERS_DESCRIPTOR_BINDING_TYPE__



#include <cstddef> // size_t



namespace RDTY::WRAPPERS
{
	enum class DescriptorBindingType : size_t
	{
		UNIFORM_BLOCK,
		STORAGE_BLOCK,
	};
}



#endif
