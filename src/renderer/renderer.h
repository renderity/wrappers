#ifndef __RDTY_WRAPPERS_RENDERER__
#define __RDTY_WRAPPERS_RENDERER__



// size_t
#include <cstddef>

#include "wrappers/src/base/base.h"



namespace RDTY
{
	namespace WRAPPERS
	{
		struct Renderer : public Base
		{
			size_t width {};
			size_t height {};
		};
	}
}



#endif
