#ifndef __RDTY_WRAPPERS_SCENE__
#define __RDTY_WRAPPERS_SCENE__



#include <cstdint>
#include <vector>

#include "wrappers/src/base/base.h"
#include "wrappers/src/object/object.h"



namespace RDTY::WRAPPERS
{
	struct alignas (16) Box
	{
		float min [3] {};

		uint32_t triangle_start {};

		float max [3] {};

		uint32_t triangle_end {};
	};



	struct Scene : public Base
	{
		// TODO: rename to position_data
		std::vector<float> position_data {};
		std::vector<float> normal_data {};
		std::vector<float> color_data {};

		std::vector<uint32_t> index_data {};

		std::vector<Object*> objects {};

		size_t triangle_count {};
		Box boxes [1024 * 1024 * 8] {};
		uint32_t triangles [1024 * 1024] {};



		// void addObject (Object&);
		// void addObject (Object*);
		// This fails since vector of references is disallowed!
		// void addObjects (std::vector<Object&>);
		void addObjects (std::vector<Object*>);

		bool testTriangle (const size_t&, float*, float*);
		void test (void);
	};
}



#endif
