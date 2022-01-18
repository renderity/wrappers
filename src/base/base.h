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
			void* impl_opengl {};
			void* impl_vulkan {};
		};
	}
}



#endif
