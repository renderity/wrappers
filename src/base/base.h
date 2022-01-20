#ifndef __RDTY_WRAPPERS_BASE__
#define __RDTY_WRAPPERS_BASE__



// #include <cstddef> // size_t
#include <string>



namespace RDTY::WRAPPERS
{
	struct Base
	{
		void* impl_opengl {};
		void* impl_vulkan {};
	};
}



#endif
