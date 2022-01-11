#ifndef __RDTY_WRAPPERS_BASE__
#define __RDTY_WRAPPERS_BASE__



// size_t
#include <cstddef>
#include <string>



namespace RDTY
{
	namespace WRAPPERS
	{
		struct Base
		{
			void* opengl_impl {};
			void* vulkan_impl {};
		};
	}
}



#endif
