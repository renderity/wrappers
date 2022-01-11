#ifndef __RDTY_WRAPPERS_UNIFORM__
#define __RDTY_WRAPPERS_UNIFORM__



// size_t
#include <cstddef>
#include <string>

#include "wrappers/src/base/base.h"



namespace RDTY
{
	namespace WRAPPERS
	{
		struct Uniform : public Base
		{
			void* object_addr {};

			std::string name {};

			size_t block_index {};

			size_t size {};
		};
	}
}



#endif
