#ifndef __RDTY_WRAPPERS_UNIFORM__
#define __RDTY_WRAPPERS_UNIFORM__



#include <cstddef> // size_t
#include <string>

#include "wrappers/src/base/base.h"



namespace RDTY::WRAPPERS
{
	struct Uniform : public Base
	{
		void* object_addr {};

		std::string name {};

		size_t block_index {};

		size_t size {};
	};
}



#endif
