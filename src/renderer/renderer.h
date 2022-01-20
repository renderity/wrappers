#ifndef __RDTY_WRAPPERS_RENDERER__
#define __RDTY_WRAPPERS_RENDERER__



#include <cstddef> // size_t

// #ifdef __wasm__
#include "wrappers/src/base/base.h"



namespace RDTY::WRAPPERS
{
	// #ifdef __wasm__
	struct Renderer : public Base
	{
		size_t width {};
		size_t height {};
	};
}



#endif
