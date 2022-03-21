#ifndef __RDTY_WRAPPERS_DESCRIPTOR_BINDING__
#define __RDTY_WRAPPERS_DESCRIPTOR_BINDING__



#include <cstddef> // size_t



namespace RDTY::WRAPPERS
{
	namespace DESCRIPTOR_BINDING
	{
		enum class Visibility : size_t
		{
			VERTEX,
			FRAGMENT,
			COMPUTE,
		};

		enum class Type : size_t
		{
			UNIFORM_BLOCK,
			STORAGE_BLOCK,
		};
	}
}



#endif
