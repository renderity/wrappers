#ifndef __RDTY_WRAPPERS_SCENE__
#define __RDTY_WRAPPERS_SCENE__



#include <vector>

#include "wrappers/src/base/base.h"
#include "wrappers/src/object/object.h"



namespace RDTY::WRAPPERS
{
	struct Scene : public Base
	{
		// TODO: rename to position_data
		std::vector<float> position_data {};
		std::vector<float> normal_data {};
		std::vector<float> color_data {};

		std::vector<uint32_t> index_data {};



		void addObject (Object&);
		void addObject (Object*);
	};
}



#endif
